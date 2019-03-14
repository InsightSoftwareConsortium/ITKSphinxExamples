/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkBinaryImageToLevelSetImageAdaptor.h"
#include "itkImageFileReader.h"
#include "itkLevelSetIterationUpdateCommand.h"
#include "itkLevelSetContainer.h"
#include "itkLevelSetEquationChanAndVeseInternalTerm.h"
#include "itkLevelSetEquationChanAndVeseExternalTerm.h"
#include "itkLevelSetEquationContainer.h"
#include "itkLevelSetEquationTermContainer.h"
#include "itkLevelSetEvolution.h"
#include "itkLevelSetEvolutionNumberOfIterationsStoppingCriterion.h"
#include "itkLevelSetDenseImage.h"
#include "itkVTKVisualizeImageLevelSetIsoValues.h"
#include "itkSinRegularizedHeavisideStepFunction.h"

int main( int argc, char* argv[] )
{
  if( argc != 3)
    {
    std::cerr << "Missing Arguments" << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << "1- Input Image" << std::endl;
    std::cerr << "2- Number of Iterations" << std::endl;
    return EXIT_FAILURE;
    }

  // Image Dimension
  constexpr unsigned int Dimension = 2;

  using InputPixelType = unsigned char;
  using InputImageType = itk::Image< InputPixelType, Dimension >;

  // Read input image (to be processed).
  using ReaderType = itk::ImageFileReader< InputImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  InputImageType::Pointer input = reader->GetOutput();

  int numberOfIterations = std::stoi( argv[2] );

  using LevelSetPixelType = float;
  using LevelSetImageType = itk::Image< LevelSetPixelType, Dimension >;
  using LevelSetType = itk::LevelSetDenseImage< LevelSetImageType >;

  using LevelSetOutputType = LevelSetType::OutputType;
  using LevelSetRealType = LevelSetType::OutputRealType;

  // Generate a binary mask that will be used as initialization for the level
  // set evolution.
  using BinaryImageType = itk::Image< LevelSetOutputType, Dimension >;
  BinaryImageType::Pointer binary = BinaryImageType::New();
  binary->SetRegions( input->GetLargestPossibleRegion() );
  binary->CopyInformation( input );
  binary->Allocate();
  binary->FillBuffer( itk::NumericTraits< LevelSetOutputType >::Zero );

  BinaryImageType::RegionType region;
  BinaryImageType::IndexType  index;
  BinaryImageType::SizeType   size;

  index.Fill( 5 );
  size.Fill( 120 );

  region.SetIndex( index );
  region.SetSize( size );

  using InputIteratorType = itk::ImageRegionIteratorWithIndex< BinaryImageType >;
  InputIteratorType iIt( binary, region );
  iIt.GoToBegin();
  while( !iIt.IsAtEnd() )
    {
    iIt.Set( itk::NumericTraits< LevelSetOutputType >::One );
    ++iIt;
    }

  // convert a binary mask to a level-set function
  using BinaryImageToLevelSetType = itk::BinaryImageToLevelSetImageAdaptor< BinaryImageType,
    LevelSetType >;

  BinaryImageToLevelSetType::Pointer adaptor = BinaryImageToLevelSetType::New();
  adaptor->SetInputImage( binary );
  adaptor->Initialize();
  LevelSetType::Pointer levelSet = adaptor->GetModifiableLevelSet();

  // The Heaviside function
  using HeavisideFunctionType = itk::SinRegularizedHeavisideStepFunction< LevelSetRealType, LevelSetRealType >;
  HeavisideFunctionType::Pointer heaviside = HeavisideFunctionType::New();
  heaviside->SetEpsilon( 1.5 );

  // Create the level set container
  using LevelSetContainerType = itk::LevelSetContainer< itk::IdentifierType, LevelSetType >;
  LevelSetContainerType::Pointer levelSetContainer = LevelSetContainerType::New();
  levelSetContainer->SetHeaviside( heaviside );
  levelSetContainer->AddLevelSet( 0, levelSet );

  // Create the terms.
  //
  // // Chan and Vese internal term
  using ChanAndVeseInternalTermType = itk::LevelSetEquationChanAndVeseInternalTerm< InputImageType, LevelSetContainerType >;
  ChanAndVeseInternalTermType::Pointer cvInternalTerm = ChanAndVeseInternalTermType::New();
  cvInternalTerm->SetInput( input );
  cvInternalTerm->SetCoefficient( 0.5 );

  // // Chan and Vese external term
  using ChanAndVeseExternalTermType = itk::LevelSetEquationChanAndVeseExternalTerm< InputImageType, LevelSetContainerType >;
  ChanAndVeseExternalTermType::Pointer cvExternalTerm = ChanAndVeseExternalTermType::New();
  cvExternalTerm->SetInput( input );

  // Create term container (equation rhs)
  using TermContainerType = itk::LevelSetEquationTermContainer< InputImageType, LevelSetContainerType >;
  TermContainerType::Pointer termContainer = TermContainerType::New();
  termContainer->SetLevelSetContainer( levelSetContainer );
  termContainer->SetInput( input );
  termContainer->AddTerm( 0, cvInternalTerm );
  termContainer->AddTerm( 1, cvExternalTerm );

  // Create equation container
  using EquationContainerType = itk::LevelSetEquationContainer< TermContainerType >;
  EquationContainerType::Pointer equationContainer = EquationContainerType::New();
  equationContainer->SetLevelSetContainer( levelSetContainer );
  equationContainer->AddEquation( 0, termContainer );

  // Create stopping criteria
  using StoppingCriterionType = itk::LevelSetEvolutionNumberOfIterationsStoppingCriterion< LevelSetContainerType >;
  StoppingCriterionType::Pointer criterion = StoppingCriterionType::New();
  criterion->SetNumberOfIterations( numberOfIterations );

  // Create the visualizer
  using VisualizationType = itk::VTKVisualizeImageLevelSetIsoValues< InputImageType, LevelSetType >;
  VisualizationType::Pointer visualizer = VisualizationType::New();
  visualizer->SetInputImage( input );
  visualizer->SetLevelSet( levelSet );
  visualizer->SetScreenCapture( true );

  // Create evolution class
  using LevelSetEvolutionType = itk::LevelSetEvolution< EquationContainerType, LevelSetType >;
  LevelSetEvolutionType::Pointer evolution = LevelSetEvolutionType::New();
  evolution->SetEquationContainer( equationContainer );
  evolution->SetStoppingCriterion( criterion );
  evolution->SetLevelSetContainer( levelSetContainer );

  using IterationUpdateCommandType = itk::LevelSetIterationUpdateCommand< LevelSetEvolutionType, VisualizationType >;
  IterationUpdateCommandType::Pointer iterationUpdateCommand = IterationUpdateCommandType::New();
  iterationUpdateCommand->SetFilterToUpdate( visualizer );
  iterationUpdateCommand->SetUpdatePeriod( 5 );

  evolution->AddObserver( itk::IterationEvent(), iterationUpdateCommand );

  evolution->Update();

  return EXIT_SUCCESS;
}

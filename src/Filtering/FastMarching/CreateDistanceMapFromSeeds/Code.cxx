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

#include "itkFastMarchingImageToNodePairContainerAdaptor.h"
#include "itkFastMarchingImageFilterBase.h"
#include "itkFastMarchingThresholdStoppingCriterion.h"
#include "itkImageFileWriter.h"

int main(int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputFileName>" << std::endl;

    return EXIT_FAILURE;
    }

  // create a fastmarching object
  using PixelType = float;
  constexpr unsigned int Dimension = 2;

  using FloatImageType = itk::Image< PixelType, Dimension >;

  using CriterionType = itk::FastMarchingThresholdStoppingCriterion< FloatImageType,
    FloatImageType >;

  using FastMarchingType = itk::FastMarchingImageFilterBase< FloatImageType, FloatImageType >;

  CriterionType::Pointer criterion = CriterionType::New();
  criterion->SetThreshold( 100. );

  FastMarchingType::Pointer marcher = FastMarchingType::New();
  marcher->SetStoppingCriterion( criterion );

  // specify the size of the output image
  FloatImageType::SizeType size = {{64,64}};
  marcher->SetOutputSize( size );

  // setup a speed image of ones
  FloatImageType::Pointer speedImage = FloatImageType::New();

  FloatImageType::RegionType region;
  region.SetSize( size );

  speedImage->SetLargestPossibleRegion( region );
  speedImage->SetBufferedRegion( region );
  speedImage->Allocate();
  speedImage->FillBuffer( 1.0 );

  // setup a 'alive image'
  FloatImageType::Pointer AliveImage = FloatImageType::New();
  AliveImage->SetLargestPossibleRegion( region );
  AliveImage->SetBufferedRegion( region );
  AliveImage->Allocate();
  AliveImage->FillBuffer( 0.0 );

  FloatImageType::OffsetType offset0 = {{28,35}};

  FloatImageType::IndexType index;
  index.Fill(0);
  index += offset0;

  AliveImage->SetPixel( index, 1.0 );

  // setup a 'trial image'
  FloatImageType::Pointer TrialImage = FloatImageType::New();
  TrialImage->SetLargestPossibleRegion( region );
  TrialImage->SetBufferedRegion( region );
  TrialImage->Allocate();
  TrialImage->FillBuffer( 0.0 );

  index[0] += 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] -= 1;
  index[1] += 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] -= 1;
  index[1] -= 1;
  TrialImage->SetPixel( index, 1.0 );

  index[0] += 1;
  index[1] -= 1;
  TrialImage->SetPixel( index, 1.0 );

  marcher->SetInput( speedImage );

  using AdaptorType = itk::FastMarchingImageToNodePairContainerAdaptor< FloatImageType,
      FloatImageType, FloatImageType >;

  AdaptorType::Pointer adaptor = AdaptorType::New();

  adaptor->SetAliveImage( AliveImage.GetPointer() );
  adaptor->SetAliveValue( 0.0 );

  adaptor->SetTrialImage( TrialImage.GetPointer() );
  adaptor->SetTrialValue( 1.0 );
  adaptor->Update();

  marcher->SetAlivePoints( adaptor->GetAlivePoints() );
  marcher->SetTrialPoints( adaptor->GetTrialPoints() );

  using WriterType = itk::ImageFileWriter< FloatImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( marcher->GetOutput() );
  writer->SetFileName( argv[1] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

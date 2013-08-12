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

#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "vtkRenderWindowInteractor.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Missing Arguments" << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << "<Input Image> <Interactive (0 or 1)>" << std::endl;
    return EXIT_FAILURE;
    }

  // Image Dimension
  const unsigned int Dimension = 2;

  typedef unsigned char                            InputPixelType;
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;

  // Read input image (to be processed).
  typedef itk::ImageFileReader< InputImageType >   ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  InputImageType::Pointer input = reader->GetOutput();

  typedef float                                         LevelSetPixelType;
  typedef itk::Image< LevelSetPixelType, Dimension >    LevelSetImageType;
  typedef itk::LevelSetDenseImage< LevelSetImageType >  LevelSetType;

  typedef LevelSetType::OutputType                      LevelSetOutputType;
  typedef LevelSetType::OutputRealType                  LevelSetRealType;

  // Generate a binary mask that will be used as initialization for the level
  // set evolution.
  typedef itk::OtsuMultipleThresholdsImageFilter< InputImageType, LevelSetImageType > OtsuFilterType;
  OtsuFilterType::Pointer otsu = OtsuFilterType::New();
  otsu->SetInput( input );
  otsu->SetNumberOfHistogramBins( 256 );
  otsu->SetNumberOfThresholds( 1 );
  otsu->Update();

  typedef itk::RescaleIntensityImageFilter< LevelSetImageType, LevelSetImageType > RescaleType;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput( otsu->GetOutput() );
  rescaler->SetOutputMinimum( 0 );
  rescaler->SetOutputMaximum( 1 );
  rescaler->Update();

  // convert a binary mask to a level-set function
  typedef itk::BinaryImageToLevelSetImageAdaptor< LevelSetImageType,
    LevelSetType > BinaryImageToLevelSetType;

  BinaryImageToLevelSetType::Pointer adaptor = BinaryImageToLevelSetType::New();
  adaptor->SetInputImage( rescaler->GetOutput() );
  adaptor->Initialize();

  LevelSetType::Pointer levelSet = adaptor->GetLevelSet();

  // Create the visualizer
  typedef itk::VTKVisualizeImageLevelSetIsoValues< InputImageType, LevelSetType > VisualizationType;
  VisualizationType::Pointer visualizer = VisualizationType::New();
  visualizer->SetInputImage( input );
  visualizer->SetLevelSet( levelSet );

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( visualizer->GetRenderWindow() );

  visualizer->Update();

  bool interactive = ( atoi( argv[2] ) != 0 );
  if( interactive )
    {
    renderWindowInteractor->Start();
    }

  return EXIT_SUCCESS;
}

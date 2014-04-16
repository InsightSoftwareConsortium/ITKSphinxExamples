#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <numberOfIterations> <timeStep> <conductance>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 2;

  typedef float                                    InputPixelType;
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef unsigned char                            OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  const int numberOfIterations     = atoi( argv[3] );
  const InputPixelType timeStep    = atof( argv[4] );
  const InputPixelType conductance = atof( argv[5] );

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::CurvatureAnisotropicDiffusionImageFilter< InputImageType, InputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetNumberOfIterations( numberOfIterations );
  filter->SetTimeStep( timeStep );
  filter->SetConductanceParameter( conductance );

  typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > RescaleType;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput( filter->GetOutput() );
  rescaler->SetOutputMinimum( itk::NumericTraits< OutputPixelType >::min() );
  rescaler->SetOutputMaximum( itk::NumericTraits< OutputPixelType >::max() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( rescaler->GetOutput() );

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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkIdentityTransform.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <size X> <size Y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  ImageType::SizeType outputSize;

  for( unsigned int dim = 0, k = 3; dim < Dimension; dim++ )
    {
    outputSize[dim] = atoi( argv[k++] );
    }

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );
  reader->UpdateOutputInformation();

  ImageType::Pointer inputImage = reader->GetOutput();

  ImageType::SizeType     inputSize     = inputImage->GetLargestPossibleRegion().GetSize();
  std::cout << "Input Size: " << inputSize << std::endl;

  ImageType::SpacingType  inputSpacing  = inputImage->GetSpacing();
  std::cout << "Input Spacing: " << inputSpacing << std::endl;

  ImageType::SpacingType  outputSpacing;

  for( unsigned int dim = 0; dim < Dimension; dim++ )
    {
    outputSpacing[dim] = static_cast< double >( inputSpacing[dim] ) * static_cast< double >( inputSize[dim] ) / static_cast< double >( outputSize[dim] );
    }

  std::cout << "Output Size: " << outputSize << std::endl;
  std::cout << "Output Spacing: " << outputSpacing << std::endl;

  typedef double TransformPrecisionType;
  typedef itk::IdentityTransform< TransformPrecisionType, Dimension > TransformType;
  typedef itk::ResampleImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( inputImage );
  filter->SetSize( outputSize );
  filter->SetOutputSpacing( outputSpacing );
  filter->SetOutputOrigin( inputImage->GetOrigin() );
  filter->SetTransform( TransformType::New() );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( filter->GetOutput() );
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

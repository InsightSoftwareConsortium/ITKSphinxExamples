#include "itkImage.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryBallStructuringElement.h"

int main(int argc, char *argv[])
{
  if( argc < 4 )
    {
    std::cerr << "Usage: " << argv[0] << " <inputImage> <outputImage> <radius>" << std::endl;
    return EXIT_FAILURE;
    }
  typedef unsigned char PixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image< PixelType, Dimension >    ImageType;
  typedef itk::ImageFileReader< ImageType >     ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::BinaryBallStructuringElement< PixelType, Dimension > StructuringElementType;
  StructuringElementType structuringElement;
  structuringElement.SetRadius( atoi( argv[3] ) );
  structuringElement.CreateStructuringElement();

  typedef itk::BinaryDilateImageFilter< ImageType, ImageType, StructuringElementType > BinaryDilateImageFilterType;

  BinaryDilateImageFilterType::Pointer dilateFilter = BinaryDilateImageFilterType::New();
  dilateFilter->SetInput( reader->GetOutput() );
  dilateFilter->SetKernel( structuringElement );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( dilateFilter->GetOutput() );
  writer->SetFileName( argv[2] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    }

  return EXIT_SUCCESS;
}

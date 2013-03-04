#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkOpenCVImageBridge.h"

// includes from OpenCV
#include "cv.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  cv::Mat img = itk::OpenCVImageBridge::ITKImageToCVMat< ImageType >( reader->GetOutput() );

  cv::imwrite( argv[2], img );

  return EXIT_SUCCESS;
}

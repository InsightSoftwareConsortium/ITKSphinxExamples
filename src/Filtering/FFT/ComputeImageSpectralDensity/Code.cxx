#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkIntensityWindowingImageFilter.h"
#include "itkFFTShiftImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 3;

  typedef float                              PixelType;
  typedef itk::Image< PixelType, Dimension > RealImageType;

  typedef itk::ImageFileReader< RealImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  typedef itk::WrapPadImageFilter< RealImageType, RealImageType > PadFilterType;
  PadFilterType::Pointer padFilter = PadFilterType::New();
  padFilter->SetInput( reader->GetOutput() );
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound( padding );

  typedef itk::ForwardFFTImageFilter< RealImageType > ForwardFFTFilterType;
  typedef ForwardFFTFilterType::OutputImageType ComplexImageType;
  ForwardFFTFilterType::Pointer forwardFFTFilter = ForwardFFTFilterType::New();
  forwardFFTFilter->SetInput( padFilter->GetOutput() );

  typedef itk::ComplexToModulusImageFilter< ComplexImageType, RealImageType >
     ComplexToModulusFilterType;
  ComplexToModulusFilterType::Pointer complexToModulusFilter
    = ComplexToModulusFilterType::New();
  complexToModulusFilter->SetInput( forwardFFTFilter->GetOutput() );

  // Window and shift the output for visualization.
  typedef unsigned short                           OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;
  typedef itk::IntensityWindowingImageFilter< RealImageType, OutputImageType >
    WindowingFilterType;
  WindowingFilterType::Pointer windowingFilter
    = WindowingFilterType::New();
  windowingFilter->SetInput( complexToModulusFilter->GetOutput() );
  windowingFilter->SetWindowMinimum( 0 );
  windowingFilter->SetWindowMaximum( 20000 );

  typedef itk::FFTShiftImageFilter< OutputImageType, OutputImageType > FFTShiftFilterType;
  FFTShiftFilterType::Pointer fftShiftFilter = FFTShiftFilterType::New();
  fftShiftFilter->SetInput( windowingFilter->GetOutput() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( fftShiftFilter->GetOutput() );
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

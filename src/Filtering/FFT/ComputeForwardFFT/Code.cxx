#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <Real filename> <Imaginary filename> <Modulus filename>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * realFileName = argv[2];
  const char * imaginaryFileName = argv[3];
  const char * modulusFileName = argv[4];

  const unsigned int Dimension = 3;

  typedef float                                   FloatPixelType;
  typedef itk::Image< FloatPixelType, Dimension > FloatImageType;

  typedef itk::ImageFileReader< FloatImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef unsigned char UnsignedCharPixelType;
  typedef itk::Image< UnsignedCharPixelType, Dimension > UnsignedCharImageType;

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  typedef itk::WrapPadImageFilter< FloatImageType, FloatImageType > PadFilterType;
  PadFilterType::Pointer padFilter = PadFilterType::New();
  padFilter->SetInput( reader->GetOutput() );
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound( padding );

  typedef itk::ForwardFFTImageFilter< FloatImageType > FFTType;
  FFTType::Pointer fftFilter = FFTType::New();
  fftFilter->SetInput( padFilter->GetOutput() );

  typedef FFTType::OutputImageType FFTOutputImageType;

  // Extract the real part
  typedef itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType> RealFilterType;
  RealFilterType::Pointer realFilter = RealFilterType::New();
  realFilter->SetInput(fftFilter->GetOutput());

  typedef itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType > RescaleFilterType;
  RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
  realRescaleFilter->SetInput(realFilter->GetOutput());
  realRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  realRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  typedef itk::ImageFileWriter< UnsignedCharImageType > WriterType;
  WriterType::Pointer realWriter = WriterType::New();
  realWriter->SetFileName( realFileName );
  realWriter->SetInput( realRescaleFilter->GetOutput() );
  try
    {
    realWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  // Extract the imaginary part
  typedef itk::ComplexToImaginaryImageFilter< FFTOutputImageType, FloatImageType> ImaginaryFilterType;
  ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
  imaginaryFilter->SetInput(fftFilter->GetOutput());

  RescaleFilterType::Pointer imaginaryRescaleFilter = RescaleFilterType::New();
  imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
  imaginaryRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  imaginaryRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  WriterType::Pointer complexWriter = WriterType::New();
  complexWriter->SetFileName( imaginaryFileName );
  complexWriter->SetInput( imaginaryRescaleFilter->GetOutput() );
  try
    {
    complexWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  // Compute the magnitude
  typedef itk::ComplexToModulusImageFilter< FFTOutputImageType, FloatImageType> ModulusFilterType;
  ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
  modulusFilter->SetInput(fftFilter->GetOutput());

  RescaleFilterType::Pointer magnitudeRescaleFilter = RescaleFilterType::New();
  magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
  magnitudeRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  magnitudeRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  WriterType::Pointer magnitudeWriter = WriterType::New();
  magnitudeWriter->SetFileName( modulusFileName );
  magnitudeWriter->SetInput( magnitudeRescaleFilter->GetOutput() );
  try
    {
    magnitudeWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

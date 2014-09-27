#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
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

  const unsigned int Dimension = 3;

  typedef float                                   FloatPixelType;
  typedef itk::Image< FloatPixelType, Dimension > FloatImageType;

  typedef itk::ImageFileReader< FloatImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef unsigned char UnsignedCharPixelType;
  typedef itk::Image< UnsignedCharPixelType, Dimension > UnsignedCharImageType;

  typedef itk::ForwardFFTImageFilter< FloatImageType > FFTType;
  FFTType::Pointer fftFilter = FFTType::New();
  fftFilter->SetInput( reader->GetOutput() );
  fftFilter->Update();

  typedef FFTType::OutputImageType FFTOutputImageType;

  // Extract the real part
  typedef itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType> RealFilterType;
  RealFilterType::Pointer realFilter = RealFilterType::New();
  realFilter->SetInput(fftFilter->GetOutput());
  realFilter->Update();

  typedef itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType > RescaleFilterType;
  RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
  realRescaleFilter->SetInput(realFilter->GetOutput());
  realRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  realRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );
  realRescaleFilter->Update();

  typedef itk::ImageFileWriter< UnsignedCharImageType > WriterType;
  WriterType::Pointer realWriter = WriterType::New();
  realWriter->SetFileName( argv[2] );
  realWriter->SetInput( realRescaleFilter->GetOutput() );
  realWriter->Update();

  // Extract the imaginary part
  typedef itk::ComplexToImaginaryImageFilter< FFTOutputImageType, FloatImageType> ImaginaryFilterType;
  ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
  imaginaryFilter->SetInput(fftFilter->GetOutput());
  imaginaryFilter->Update();

  RescaleFilterType::Pointer imaginaryRescaleFilter = RescaleFilterType::New();
  imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
  imaginaryRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  imaginaryRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );
  imaginaryRescaleFilter->Update();

  WriterType::Pointer complexWriter = WriterType::New();
  complexWriter->SetFileName( argv[3] );
  complexWriter->SetInput( imaginaryRescaleFilter->GetOutput() );
  complexWriter->Update();

  // Compute the magnitude
  typedef itk::ComplexToModulusImageFilter< FFTOutputImageType, FloatImageType> ModulusFilterType;
  ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
  modulusFilter->SetInput(fftFilter->GetOutput());
  modulusFilter->Update();

  RescaleFilterType::Pointer magnitudeRescaleFilter = RescaleFilterType::New();
  magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
  magnitudeRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  magnitudeRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );
  magnitudeRescaleFilter->Update();

  WriterType::Pointer magnitudeWriter = WriterType::New();
  magnitudeWriter->SetFileName( argv[4] );
  magnitudeWriter->SetInput( magnitudeRescaleFilter->GetOutput() );
  magnitudeWriter->Update();

  return EXIT_SUCCESS;
}

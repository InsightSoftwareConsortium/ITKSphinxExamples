#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkGaussianImageSource.h"
#include "itkFFTShiftImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkInverseFFTImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " [Sigma]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  double sigmaValue = 0.5;
  if( argc > 3 )
    {
    sigmaValue = atof( argv[3] );
    }

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

  try
    {
    forwardFFTFilter->UpdateOutputInformation();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  // A Gaussian is used here to create a low-pass filter.
  typedef itk::GaussianImageSource< RealImageType > GaussianSourceType;
  GaussianSourceType::Pointer gaussianSource = GaussianSourceType::New();
  gaussianSource->SetNormalized( true );
  ComplexImageType::ConstPointer transformedInput
    = forwardFFTFilter->GetOutput();
  const ComplexImageType::RegionType inputRegion(
    transformedInput->GetLargestPossibleRegion() );
  const ComplexImageType::SizeType inputSize
    = inputRegion.GetSize();
  const ComplexImageType::SpacingType inputSpacing =
    transformedInput->GetSpacing();
  const ComplexImageType::PointType inputOrigin =
    transformedInput->GetOrigin();
  const ComplexImageType::DirectionType inputDirection =
    transformedInput->GetDirection();
  gaussianSource->SetSize( inputSize );
  gaussianSource->SetSpacing( inputSpacing );
  gaussianSource->SetOrigin( inputOrigin );
  gaussianSource->SetDirection( inputDirection );
  GaussianSourceType::ArrayType sigma;
  GaussianSourceType::PointType mean;
  sigma.Fill( sigmaValue );
  for( unsigned int ii = 0; ii < Dimension; ++ii )
    {
    const double halfLength = inputSize[ii] * inputSpacing[ii] / 2.0;
    sigma[ii] *= halfLength;
    mean[ii] = inputOrigin[ii] + halfLength;
    }
  mean = inputDirection * mean;
  gaussianSource->SetSigma( sigma );
  gaussianSource->SetMean( mean );

  typedef itk::FFTShiftImageFilter< RealImageType, RealImageType > FFTShiftFilterType;
  FFTShiftFilterType::Pointer fftShiftFilter = FFTShiftFilterType::New();
  fftShiftFilter->SetInput( gaussianSource->GetOutput() );

  typedef itk::MultiplyImageFilter< ComplexImageType,
                                    RealImageType,
                                    ComplexImageType >
                                      MultiplyFilterType;
  MultiplyFilterType::Pointer multiplyFilter = MultiplyFilterType::New();
  multiplyFilter->SetInput1( forwardFFTFilter->GetOutput() );
  multiplyFilter->SetInput2( fftShiftFilter->GetOutput() );

  typedef itk::InverseFFTImageFilter< ComplexImageType, RealImageType >
    InverseFilterType;
  InverseFilterType::Pointer inverseFFTFilter = InverseFilterType::New();
  inverseFFTFilter->SetInput( multiplyFilter->GetOutput() );

  typedef itk::ImageFileWriter< RealImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( inverseFFTFilter->GetOutput() );
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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageToHistogramFilter.h"
#include "itkImageRandomIteratorWithIndex.h"

int main(int argc, char* argv[])
{
  if( argc != 3 )
    {
    std::cerr << argv[0] << "InputFileName NumberOfBins" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  const unsigned int MeasurementVectorSize = 1; // Grayscale
  const unsigned int binsPerDimension =
    static_cast< unsigned int >( atoi( argv[2] ) );

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

  ImageType::Pointer image = reader->GetOutput();

  typedef itk::Statistics::ImageToHistogramFilter< ImageType >
    ImageToHistogramFilterType;

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType
    lowerBound(binsPerDimension);
  lowerBound.Fill(0);

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType
    upperBound(binsPerDimension);
  upperBound.Fill(255) ;

  ImageToHistogramFilterType::HistogramType::SizeType
    size(MeasurementVectorSize);
  size.Fill(binsPerDimension);

  ImageToHistogramFilterType::Pointer imageToHistogramFilter =
    ImageToHistogramFilterType::New();
  imageToHistogramFilter->SetInput( image );
  imageToHistogramFilter->SetHistogramBinMinimum( lowerBound );
  imageToHistogramFilter->SetHistogramBinMaximum( upperBound );
  imageToHistogramFilter->SetHistogramSize( size );
  imageToHistogramFilter->Update();

  ImageToHistogramFilterType::HistogramType* histogram =
    imageToHistogramFilter->GetOutput();

  std::cout << "Frequency = ";
  for(unsigned int i = 0; i < histogram->GetSize()[0]; ++i)
    {
    std::cout << histogram->GetFrequency(i) << " ";
    }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}

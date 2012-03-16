#include "itkMedianImageFilter.h"

#include "itkRGBPixel.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

namespace itk
{
/** \class myRGBPixel
 * \brief Extends RGBPixel with operator <=
 *
 * This class overrides the <= and < operators to use Luminance as a sorting
 * value.
 */
< typename TComponent = unsigned short >
class myRGBPixel : public RGBPixel<TComponent>
{
public:
  typedef myRGBPixel           Self;
  typedef RGBPixel<TComponent> Superclass;

  using RGBPixel<TComponent>::operator=;

  bool operator<=(const Self & r) const
    {
    return (this->GetLuminance() <= r.GetLuminance());
    }
  bool operator<(const Self & r) const
    {
    return (this->GetLuminance() < r.GetLuminance());
    }
};
}

int main(int argc, char * argv[])
{
  // Verify command line arguments
  if( argc != 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputImageFile> <OutputImageFile> <radius>"
              << std::endl;
    return EXIT_FAILURE;
    }

  // Setup types
  const unsigned int Dimension = 2;

  typedef itk::myRGBPixel< unsigned char >      MyPixelType;
  typedef itk::Image< MyPixelType, Dimension >  MyImageType;

  // Create and setup a reader
  typedef itk::ImageFileReader< MyImageType >                 ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  // Create and setup a median filter
  typedef itk::MedianImageFilter< MyImageType, MyImageType >  FilterType;
  FilterType::Pointer medianFilter = FilterType::New();

  FilterType::InputSizeType radius;
  radius.Fill( atoi( argv[3] ) );

  medianFilter->SetRadius( radius );
  medianFilter->SetInput( reader->GetOutput() );
  medianFilter->Update();

  // Cast the custom myRBGPixel's to RGBPixel's
  typedef itk::RGBPixel< unsigned char >                      RGBPixelType;
  typedef itk::Image< RGBPixelType, Dimension >               RGBImageType;
  typedef itk::CastImageFilter< MyImageType, RGBImageType >   CastType;
  CastType::Pointer cast = CastType::New();
  cast->SetInput( medianFilter->GetOutput() );
  cast->Update();

  typedef itk::ImageFileWriter< RGBImageType >                WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( cast->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  return EXIT_SUCCESS;
}

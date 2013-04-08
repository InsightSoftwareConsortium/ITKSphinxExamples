#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkRGBPixel.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"


int main(int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputFileName> <OutputFileName>"
              << std::endl;

    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                   PixelType;
  typedef itk::RGBPixel< unsigned char >  RGBPixelType;

  typedef itk::Image< RGBPixelType, 2 >   RGBImageType;
  typedef itk::Image< PixelType, 2 >      ImageType;


  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::Function::CustomColormapFunction< PixelType, RGBPixelType >
    ColormapType;
  ColormapType::Pointer colormap = ColormapType::New();

  ColormapType::ChannelType redChannel;
  ColormapType::ChannelType greenChannel;
  ColormapType::ChannelType blueChannel;

  itk::Statistics::MersenneTwisterRandomVariateGenerator::Pointer random =
    itk::Statistics::MersenneTwisterRandomVariateGenerator::New();

  random->SetSeed( 0 );

  for( unsigned int i = 0; i < 255; ++i )
    {
    redChannel.push_back(
      static_cast< ColormapType::RealType >(
        random->GetUniformVariate( 0., 1.0 ) ) );

    greenChannel.push_back(
      static_cast< ColormapType::RealType >(
        random->GetUniformVariate( 0., 1.0 ) ) );

    blueChannel.push_back(
      static_cast< ColormapType::RealType >(
        random->GetUniformVariate( 0., 1.0 ) ) );
    }

  colormap->SetRedChannel( redChannel );
  colormap->SetGreenChannel( greenChannel );
  colormap->SetBlueChannel( blueChannel );

  typedef itk::ScalarToRGBColormapImageFilter< ImageType, RGBImageType >
    ColormapFilterType;
  ColormapFilterType::Pointer colormapFilter1 = ColormapFilterType::New();

  colormapFilter1->SetInput( reader->GetOutput() );
  colormapFilter1->SetColormap( colormap );
  colormapFilter1->Update();

  typedef itk::ImageFileWriter< RGBImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( colormapFilter1->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  return EXIT_SUCCESS;
}

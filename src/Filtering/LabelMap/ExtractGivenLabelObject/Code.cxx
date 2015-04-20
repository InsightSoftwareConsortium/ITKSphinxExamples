#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLabelObject.h"
#include "itkLabelMap.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelSelectionLabelMapFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName1> <OutputFileName2> <Label>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  const char * inputFileName = argv[1];
  const char * outputFileName[2];
  outputFileName[0] = argv[2];
  outputFileName[1] = argv[3];
  const PixelType label = static_cast< PixelType >( atoi( argv[4] ) );

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::LabelObject< PixelType, Dimension >  LabelObjectType;
  typedef itk::LabelMap< LabelObjectType >          LabelMapType;

  typedef itk::LabelImageToLabelMapFilter< ImageType, LabelMapType > LabelImageToLabelMapFilterType;
  LabelImageToLabelMapFilterType::Pointer labelMapConverter = LabelImageToLabelMapFilterType::New();
  labelMapConverter->SetInput( reader->GetOutput() );
  labelMapConverter->SetBackgroundValue( itk::NumericTraits< PixelType >::Zero );

  typedef itk::LabelSelectionLabelMapFilter< LabelMapType > SelectorType;
  SelectorType::Pointer selector = SelectorType::New();
  selector->SetInput( labelMapConverter->GetOutput() );
  selector->SetLabel( label );

  for( int i = 0; i < 2; i++ )
    {
    typedef itk::LabelMapToLabelImageFilter< LabelMapType, ImageType > LabelMapToLabelImageFilterType;
    LabelMapToLabelImageFilterType::Pointer labelImageConverter = LabelMapToLabelImageFilterType::New();
    labelImageConverter->SetInput( selector->GetOutput( i ) );

    typedef itk::ImageFileWriter< ImageType > WriterType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( outputFileName[i] );
    writer->SetInput( labelImageConverter->GetOutput() );
    try
      {
      writer->Update();
      }
    catch( itk::ExceptionObject & error )
      {
      std::cerr << "Error: " << error << std::endl;
      return EXIT_FAILURE;
      }
    }

  return EXIT_SUCCESS;
}

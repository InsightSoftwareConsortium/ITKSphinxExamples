#include "itkPipelineMonitorImageFilter.h"
#include "itkRandomImageSource.h"
#include "itkStreamingImageFilter.h"

int main( int argc, char* argv[] )
{
  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::RandomImageSource< ImageType > SourceType;
  SourceType::Pointer source = SourceType::New();
  ImageType::SizeType size;
  size.Fill( 3 );
  source->SetSize( size );

  typedef itk::PipelineMonitorImageFilter< ImageType > MonitorFilterType;
  MonitorFilterType::Pointer monitorFilter = MonitorFilterType::New();
  monitorFilter->SetInput( source->GetOutput() );
  monitorFilter->DebugOn();

  typedef itk::StreamingImageFilter< ImageType, ImageType > StreamingFilterType;
  StreamingFilterType::Pointer streamingFilter = StreamingFilterType::New();
  streamingFilter->SetInput( monitorFilter->GetOutput() );
  streamingFilter->SetNumberOfStreamDivisions( 3 );

  try
    {
    streamingFilter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

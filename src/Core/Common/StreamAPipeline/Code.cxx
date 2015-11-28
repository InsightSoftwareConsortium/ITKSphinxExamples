/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkPipelineMonitorImageFilter.h"
#include "itkRandomImageSource.h"
#include "itkStreamingImageFilter.h"

int main( int, char* [] )
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

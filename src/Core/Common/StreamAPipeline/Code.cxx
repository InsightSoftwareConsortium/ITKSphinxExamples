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

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0] << " <NumberOfSplits>" << std::endl;
    return EXIT_FAILURE;
    }
  int numberOfSplits = atoi( argv[1] );

  const unsigned int Dimension = 2;
  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::RandomImageSource< ImageType > SourceType;
  SourceType::Pointer source = SourceType::New();
  ImageType::SizeType size;
  size.Fill( numberOfSplits );
  source->SetSize( size );

  typedef itk::PipelineMonitorImageFilter< ImageType > MonitorFilterType;
  MonitorFilterType::Pointer monitorFilter = MonitorFilterType::New();
  monitorFilter->SetInput( source->GetOutput() );
  // If ITK was built with the Debug CMake configuration, the filter
  // automatically outputs status information to the console
  monitorFilter->DebugOn();

  typedef itk::StreamingImageFilter< ImageType, ImageType > StreamingFilterType;
  StreamingFilterType::Pointer streamingFilter = StreamingFilterType::New();
  streamingFilter->SetInput( monitorFilter->GetOutput() );
  streamingFilter->SetNumberOfStreamDivisions( numberOfSplits );

  try
    {
    streamingFilter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "The output LargestPossibleRegion is: "
    << streamingFilter->GetOutput()->GetLargestPossibleRegion() << std::endl;
  std::cout << std::endl;

  const MonitorFilterType::RegionVectorType updatedRequestedRegions =
    monitorFilter->GetUpdatedRequestedRegions();
  std::cout << "Updated RequestedRegions's:" << std::endl;
  for( size_t ii = 0; ii < updatedRequestedRegions.size(); ++ii )
    {
    std::cout << "  " << updatedRequestedRegions[ii] << std::endl;
    }

  return EXIT_SUCCESS;
}

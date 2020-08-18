/*=========================================================================
 *
 *  Copyright NumFOCUS
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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMedianImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const int xDiv = 6;
  const int yDiv = 4;
  const int zDiv = 1; // 1 for 2D input

  constexpr unsigned int Dimension = 3;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFileName);
  reader->UpdateOutputInformation();
  ImageType::RegionType fullRegion = reader->GetOutput()->GetLargestPossibleRegion();
  ImageType::SizeType   fullSize = fullRegion.GetSize();
  // when reading image from file, start index is always 0

  ImageType::IndexType start;
  ImageType::IndexType end;
  ImageType::SizeType  size;

  using MedianType = itk::MedianImageFilter<ImageType, ImageType>;
  MedianType::Pointer median = MedianType::New();
  median->SetInput(reader->GetOutput());
  median->SetRadius(2);

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputFileName);

  // Use for loops to split the image into chunks.
  // This way of splitting gives us easy control over it.
  // For example, we could make the regions always be of equal size
  // in order to create samples for a deep learning algorithm.
  // ImageRegionSplitterMultidimensional has a similar
  // functionality to what is implemented below.
  for (int z = 0; z < zDiv; z++)
  {
    start[2] = fullSize[2] * double(z) / zDiv;
    end[2] = fullSize[2] * (z + 1.0) / zDiv;
    size[2] = end[2] - start[2];

    for (int y = 0; y < yDiv; y++)
    {
      start[1] = fullSize[1] * double(y) / yDiv;
      end[1] = fullSize[1] * (y + 1.0) / yDiv;
      size[1] = end[1] - start[1];

      for (int x = 0; x < xDiv; x++)
      {
        start[0] = fullSize[0] * double(x) / xDiv;
        end[0] = fullSize[0] * (x + 1.0) / xDiv;
        size[0] = end[0] - start[0];

        ImageType::RegionType region;
        region.SetIndex(start);
        region.SetSize(size);

        // now that we have our chunk, request the filter to only process that
        median->GetOutput()->SetRequestedRegion(region);
        median->Update();
        ImageType::Pointer result = median->GetOutput();

        // only needed in case of further manual processing
        result->DisconnectPipeline();

        // possible additional non-ITK pipeline processing

        writer->SetInput(result);

        // convert region into IO region
        itk::ImageIORegion ioRegion(Dimension);
        ioRegion.SetIndex(0, start[0]);
        ioRegion.SetIndex(1, start[1]);
        ioRegion.SetIndex(2, start[2]);
        ioRegion.SetSize(0, region.GetSize()[0]);
        ioRegion.SetSize(1, region.GetSize()[1]);
        ioRegion.SetSize(2, region.GetSize()[2]);
        // tell the writer this is only a chunk of a larger image
        writer->SetIORegion(ioRegion);

        try
        {
          writer->Update();
        }
        catch (itk::ExceptionObject & error)
        {
          std::cerr << "Exception for chunk: " << x << ' ' << y << ' ' << z << error << std::endl;
          return EXIT_FAILURE;
        }
      }
    }
  }

  return EXIT_SUCCESS;
}

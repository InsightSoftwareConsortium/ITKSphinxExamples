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

#include "itkLogImageFilter.h"
#include "itkRandomImageSource.h"
#include "itkImageDuplicator.h"
#include "itkMultiThreaderBase.h"
#include "itkImageRegionIterator.h"

constexpr unsigned int Dimension = 2;
using PixelType = unsigned int;
using ImageType = itk::Image<PixelType, Dimension>;

// calculate log(1+x), where x is pixel value, using LogImageFilter
void
log1xViaLogImageFilter(ImageType::Pointer & image)
{
  // LogImageFilter calculates log(x), so we have to modify the image first
  // by increase its every pixel value by 1, and then apply log filter to it
  itk::ImageRegionIterator<ImageType> it(image, image->GetBufferedRegion());
  for (; !it.IsAtEnd(); ++it)
  {
    it.Set(1 + it.Get());
  }

  // classic filter declaration and invocation
  using LogType = itk::LogImageFilter<ImageType, ImageType>;
  LogType::Pointer logF = LogType::New();
  logF->SetInput(image);
  logF->SetInPlace(true);
  logF->Update();
  image = logF->GetOutput();
  image->DisconnectPipeline();
}

// calculate log(1+x), where x is pixel value, using ParallelizeImageRegion
void
log1xViaParallelizeImageRegion(ImageType::Pointer & image)
{
  itk::MultiThreaderBase::Pointer mt = itk::MultiThreaderBase::New();
  // ParallelizeImageRegion invokes the provided lambda function in parallel
  // each invocation will contain a piece of the overall region
  mt->ParallelizeImageRegion<Dimension>(
    image->GetBufferedRegion(),
    // here we creat an ad-hoc lambda function to process the region pieces
    // the lambda will have access to variable 'image' from the outer function
    // it will have parameter 'region', which needs to be processed
    [image](const ImageType::RegionType & region) {
      itk::ImageRegionIterator<ImageType> it(image, region);
      for (; !it.IsAtEnd(); ++it)
      {
        it.Set(std::log(1 + it.Get()));
      }
    },
    nullptr); // we don't have a filter whose progress needs to be updated
}

int
main(int, char *[])
{
  int result = EXIT_SUCCESS;

  // create an image
  ImageType::RegionType region = { { 0, 0 }, { 50, 20 } }; // indices zero, size 50x20
  using RandomSourceType = itk::RandomImageSource<ImageType>;
  RandomSourceType::Pointer randomImageSource = RandomSourceType::New();
  randomImageSource->SetSize(region.GetSize());
  // we don't want overflow on 1+x operation, so set max pixel value
  randomImageSource->SetMax(itk::NumericTraits<PixelType>::max() - 1);
  randomImageSource->SetNumberOfWorkUnits(1); // to produce deterministic results
  randomImageSource->Update();

  ImageType::Pointer image = randomImageSource->GetOutput();
  image->DisconnectPipeline();

  // create another image, to be passed to the alternative method
  using DuplicatorType = itk::ImageDuplicator<ImageType>;
  DuplicatorType::Pointer duplicator = DuplicatorType::New();
  duplicator->SetInputImage(image);
  duplicator->Update();

  ImageType::Pointer clonedImage = duplicator->GetOutput();
  clonedImage->DisconnectPipeline();

  // invoke the two functions
  log1xViaLogImageFilter(image);
  log1xViaParallelizeImageRegion(clonedImage);

  // compare to make sure the results are the same
  unsigned                                 diffCount = 0;
  itk::ImageRegionConstIterator<ImageType> it1(image, region);
  itk::ImageRegionConstIterator<ImageType> it2(clonedImage, region);
  for (; !it1.IsAtEnd(); ++it1, ++it2)
  {
    if (it1.Get() != it2.Get())
    {
      std::cerr << "Pixel values are different at index " << it1.GetIndex() << it1.Get() << " vs. " << it2.Get()
                << std::endl;
      //<< "\n\tlog1xViaLogImageFilter's value: " << it1.Get()
      //<< "\n\tlog1xViaParallelizeImageRegion: " << it2.Get() << std::endl;
      diffCount++;
      result = EXIT_FAILURE;
    }
  }

  if (diffCount == 0)
  {
    std::cout << "LogImageFilter and ParallelizeImageRegion generate the same result." << std::endl;
  }
  else
  {
    std::cout << "Discrepancy! " << diffCount << " pixels out of " << region.GetNumberOfPixels() << " are different."
              << std::endl;
  }
  return result;
}

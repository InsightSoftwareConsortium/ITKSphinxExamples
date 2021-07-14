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
template <typename TComponent = unsigned short>
class myRGBPixel : public RGBPixel<TComponent>
{
public:
  using Self = myRGBPixel;
  using Superclass = RGBPixel<TComponent>;

  using RGBPixel<TComponent>::operator=;

  bool
  operator<=(const Self & r) const
  {
    return (this->GetLuminance() <= r.GetLuminance());
  }
  bool
  operator<(const Self & r) const
  {
    return (this->GetLuminance() < r.GetLuminance());
  }
};
} // namespace itk

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputImageFile> <OutputImageFile> <radius>" << std::endl;
    return EXIT_FAILURE;
  }

  // Setup types
  constexpr unsigned int Dimension = 2;

  using MyPixelType = itk::myRGBPixel<unsigned char>;
  using MyImageType = itk::Image<MyPixelType, Dimension>;

  const auto input = itk::ReadImage<MyImageType>(argv[1]);

  // Create and setup a median filter
  using FilterType = itk::MedianImageFilter<MyImageType, MyImageType>;
  FilterType::Pointer medianFilter = FilterType::New();

  FilterType::InputSizeType radius;
  radius.Fill(std::stoi(argv[3]));

  medianFilter->SetRadius(radius);
  medianFilter->SetInput(input);

  // Cast the custom myRBGPixel's to RGBPixel's
  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, Dimension>;
  using CastType = itk::CastImageFilter<MyImageType, RGBImageType>;
  CastType::Pointer cast = CastType::New();
  cast->SetInput(medianFilter->GetOutput());

  try
  {
    itk::WriteImage(cast->GetOutput(), argv[2]);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

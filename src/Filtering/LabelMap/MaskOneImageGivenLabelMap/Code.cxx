/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
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
#include "itkLabelObject.h"
#include "itkLabelMap.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapMaskImageFilter.h"

int
main(int argc, char * argv[])
{
  if ((argc != 6) && (argc != 9))
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <LabelMapFileName> <OutputFileName> <Label> <Background>";
    std::cerr << " [<negated (bool)> <crop (bool)> <border size>]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const char *             inputFileName = argv[1];
  const char *             labelMapFileName = argv[2];
  const char *             outputFileName = argv[3];
  const auto               label = static_cast<PixelType>(std::stoi(argv[4]));
  const auto               background = static_cast<PixelType>(std::stoi(argv[5]));
  bool                     negated = false;
  bool                     crop = false;
  ImageType::SizeValueType borderSize = 0;

  if (argc == 9)
  {
    negated = (std::stoi(argv[6]) == 1);
    crop = (std::stoi(argv[7]) == 1);
    borderSize = static_cast<ImageType::SizeValueType>(std::stoi(argv[8]));
  }

  const auto input1 = itk::ReadImage<ImageType>(inputFileName);

  const auto input2 = itk::ReadImage<ImageType>(labelMapFileName);

  using LabelObjectType = itk::LabelObject<PixelType, Dimension>;
  using LabelMapType = itk::LabelMap<LabelObjectType>;

  // convert the label image into a LabelMap
  using LabelImage2LabelMapType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;
  auto convert = LabelImage2LabelMapType::New();
  convert->SetInput(input2);

  using FilterType = itk::LabelMapMaskImageFilter<LabelMapType, ImageType>;
  auto filter = FilterType::New();
  filter->SetInput(convert->GetOutput());
  filter->SetFeatureImage(input1);

  // The label to be used to mask the image is passed via SetLabel
  filter->SetLabel(label);

  // The background in the output image (where the image is masked)
  // is passed via SetBackground
  filter->SetBackgroundValue(background);

  // The user can choose to mask the image outside the label object
  // (default behavior), or inside the label object with the chosen label,
  // by calling SetNegated().
  filter->SetNegated(negated);

  // Finally, the image can be cropped to the masked region, by calling
  // SetCrop( true ), or to a region padded by a border, by calling both
  // SetCrop() and SetCropBorder().
  // The crop border defaults to 0, and the image is not cropped by default.
  filter->SetCrop(crop);

  auto border = FilterType::SizeType::Filled(borderSize);

  filter->SetCropBorder(border);

  try
  {
    itk::WriteImage(filter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

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
#include "itkTileImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"

int
main(int argc, char * argv[])
{

  using PixelType = unsigned char;
  constexpr unsigned int InputImageDimension = 2;
  constexpr unsigned int OutputImageDimension = 3;

  using InputImageType = itk::Image<PixelType, InputImageDimension>;
  using OutputImageType = itk::Image<PixelType, OutputImageDimension>;

  using ImageReaderType = itk::ImageFileReader<InputImageType>;

  using TilerType = itk::TileImageFilter<InputImageType, OutputImageType>;

  if (argc < 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "input1 input2 ... inputn output" << std::endl;
    return EXIT_FAILURE;
  }

  TilerType::Pointer tiler = TilerType::New();

  itk::FixedArray<unsigned int, OutputImageDimension> layout;

  layout[0] = 1;
  layout[1] = 1;
  layout[2] = 0;

  tiler->SetLayout(layout);

  unsigned int inputImageNumber = 0;

  ImageReaderType::Pointer reader = ImageReaderType::New();

  InputImageType::Pointer inputImageTile;

  for (int i = 1; i < argc - 1; i++)
  {
    reader->SetFileName(argv[i]);
    reader->UpdateLargestPossibleRegion();
    inputImageTile = reader->GetOutput();
    inputImageTile->DisconnectPipeline();
    tiler->SetInput(inputImageNumber++, inputImageTile);
  }

  PixelType filler = 128;

  tiler->SetDefaultPixelValue(filler);

  tiler->Update();

  try
  {
    itk::WriteImage(tiler->GetOutput(), argv[argc - 1]);
  }
  catch (itk::ExceptionObject & excp)
  {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

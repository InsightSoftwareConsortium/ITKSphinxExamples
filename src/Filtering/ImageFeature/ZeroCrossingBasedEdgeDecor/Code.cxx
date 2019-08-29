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
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkZeroCrossingBasedEdgeDetectionImageFilter.h"

#include "itksys/SystemTools.hxx"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  double var = 5.0;
  if (argc > 2)
  {
    var = std::stod(argv[2]);
  }

  // Parse command line arguments
  std::string inputFilename = argv[1];

  // Setup types
  using FloatImageType = itk::Image<float, 2>;
  using ReaderType = itk::ImageFileReader<FloatImageType>;

  using FilterType = itk::ZeroCrossingBasedEdgeDetectionImageFilter<FloatImageType, FloatImageType>;

  // Create and setup a reader
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFilename.c_str());

  // Create and setup a derivative filter
  FilterType::Pointer edgeDetector = FilterType::New();
  edgeDetector->SetInput(reader->GetOutput());
  FilterType::ArrayType variance;
  variance.Fill(var);
  edgeDetector->SetVariance(variance);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(reader->GetOutput(), true, itksys::SystemTools::GetFilenameName(inputFilename));

  std::stringstream desc;
  desc << "ZeroBasedEdgeDetection, variance = " << edgeDetector->GetVariance();
  viewer.AddImage(edgeDetector->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

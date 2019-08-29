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
#include "itkVersion.h"

#include "itkRigid2DTransform.h"
#include "itkTransformFileWriter.h"

int
main(int argc, char * argv[])
{
  std::string fileName;
  if (argc == 1) // No arguments were provided
  {
    fileName = "test.tfm";
  }
  else
  {
    fileName = argv[1];
  }

  using TransformType = itk::Rigid2DTransform<float>;
  TransformType::Pointer transform = TransformType::New();

#if (ITK_VERSION_MAJOR == 4 && ITK_VERSION_MINOR >= 5) || ITK_VERSION_MAJOR > 4
  itk::TransformFileWriterTemplate<float>::Pointer writer = itk::TransformFileWriterTemplate<float>::New();
#else
  itk::TransformFileWriter::Pointer writer = itk::TransformFileWriter::New();
#endif

  writer->SetInput(transform);
  writer->SetFileName(fileName);
  writer->Update();

  return EXIT_SUCCESS;
}

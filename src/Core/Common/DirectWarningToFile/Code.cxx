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
#include <itkFileOutputWindow.h>
#include <itkScaleTransform.h>

int
main(int argc, char * argv[])
{
  using myFileOutputWindow = itk::FileOutputWindow;
  auto window = myFileOutputWindow::New();

  if (argc > 1)
  {
    window->SetFileName(argv[1]);
  }
  window->FlushOn();

  // Set the singelton instance
  itk::OutputWindow::SetInstance(window);

  // Generic output
  itkGenericOutputMacro("This should be in the file: " << window->GetFileName());
  // Warning
  using TransformType = itk::ScaleTransform<float, 2>;
  auto                               transform = TransformType::New();
  TransformType::FixedParametersType parameters(3);
  transform->SetFixedParameters(parameters);

  std::cout << "Look in " << window->GetFileName() << " for the output" << std::endl;
  return EXIT_SUCCESS;
}

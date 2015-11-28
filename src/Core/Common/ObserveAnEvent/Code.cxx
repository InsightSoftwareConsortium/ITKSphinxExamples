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
#include "itkBinaryNotImageFilter.h"
#include "itkCommand.h"

class MyCommand : public itk::Command
{
  public:
    itkNewMacro( MyCommand );

    void Execute(itk::Object *caller, const itk::EventObject & event)
      {
      Execute( (const itk::Object *)caller, event);
      }

    void Execute(const itk::Object *, const itk::EventObject &)
      {
      std::cout << "Command called." << std::endl;
      }

};

int main(int, char*[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;
  ImageType::Pointer image = ImageType::New();

  typedef itk::BinaryNotImageFilter< ImageType >  BinaryNotImageFilterType;

  BinaryNotImageFilterType::Pointer filter =
      BinaryNotImageFilterType::New();
  filter->SetInput(image);

  MyCommand::Pointer myCommand = MyCommand::New();
  filter->AddObserver(itk::ProgressEvent(), myCommand);

  filter->Update();

  return EXIT_SUCCESS;
}

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
#include "itkGaussianImageSource.h"
#include "itkCommand.h"

class MyCommand: public itk::Command
{
  public:
    itkNewMacro( MyCommand );

    void Execute(itk::Object * caller, const itk::EventObject & event) override
      {
      Execute( (const itk::Object *)caller, event);
      }

    void Execute(const itk::Object * caller, const itk::EventObject & event) override
      {
      if( ! itk::ProgressEvent().CheckEvent( &event ) )
        {
        return;
        }
      const auto * processObject =
        dynamic_cast< const itk::ProcessObject * >( caller );
      if( ! processObject )
        {
        return;
        }
      std::cout << "Progress: " << processObject->GetProgress() << std::endl;
      }
};


int main(int, char*[])
{
  const unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;

  using SourceType = itk::GaussianImageSource< ImageType >;
  SourceType::Pointer source = SourceType::New();

  ImageType::SizeType size;
  size.Fill( 128 );
  source->SetSize( size );

  SourceType::ArrayType sigma;
  sigma.Fill( 45.0 );
  source->SetSigma( sigma );

  MyCommand::Pointer myCommand = MyCommand::New();
  source->AddObserver(itk::ProgressEvent(), myCommand);

  source->Update();

  return EXIT_SUCCESS;
}

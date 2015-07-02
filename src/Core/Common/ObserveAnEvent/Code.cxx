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

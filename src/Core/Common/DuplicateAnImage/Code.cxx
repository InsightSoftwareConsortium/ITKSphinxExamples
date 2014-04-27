#include "itkImage.h"
#include "itkImageDuplicator.h"
#include "itkRandomImageSource.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::RandomImageSource< ImageType > RandomSourceType;

  RandomSourceType::Pointer randomImageSource = RandomSourceType::New();
  randomImageSource->SetNumberOfThreads(1); // to produce non-random results

  ImageType::Pointer image = randomImageSource->GetOutput();

  typedef itk::ImageDuplicator< ImageType > DuplicatorType;
  DuplicatorType::Pointer duplicator = DuplicatorType::New();
  duplicator->SetInputImage(image);
  duplicator->Update();

  ImageType::Pointer clonedImage = duplicator->GetOutput();

  return EXIT_SUCCESS;
}

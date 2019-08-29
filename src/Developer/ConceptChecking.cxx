#include <itkConceptChecking.h>
#include <itkImage.h>

template <typename TImage>
void
MyFunction(const TImage * const image)
{
  itkConceptMacro(nameOfCheck, (itk::Concept::IsFloatingPoint<typename TImage::ValueType>));
}

int
main(int, char *[])
{
  using FloatImageType = itk::Image<float, 2>;
  FloatImageType::Pointer floatImage = FloatImageType::New();
  MyFunction(floatImage.GetPointer());

  using DoubleImageType = itk::Image<double, 2>;
  DoubleImageType::Pointer doubleImage = DoubleImageType::New();
  MyFunction(doubleImage.GetPointer());

  // Fails the concept check
  //   using IntImageType = itk::Image<int, 2>;
  //   IntImageType::Pointer intImage = IntImageType::New();
  //   MyFunction(intImage.GetPointer());

  // Fails the concept check
  //   using UCharImageType = itk::Image<unsigned char, 2>;
  //   UCharImageType::Pointer ucharImage = UCharImageType::New();
  //   MyFunction(ucharImage.GetPointer());

  return EXIT_SUCCESS;
}

#ifndef ImageSource_h
#define ImageSource_h

#include "itkProcessObject.h"

#include <set>

namespace itk
{
template <typename TImage>
class ImageSource : public ProcessObject
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageSource);

  /** Standard class type alias. */
  using Self = ImageSource;
  using Superclass = ProcessObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ImageSource);

protected:
  ImageSource() = default;
  ~ImageSource() override = default;

  /** Does the real work. */
  virtual void
  GenerateData();
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageSource.hxx"
#endif


#endif // ImageSource_h

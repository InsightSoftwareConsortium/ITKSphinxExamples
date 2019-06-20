#ifndef itkImageFilterMultipleInputs_h
#define itkImageFilterMultipleInputs_h

#include "itkImageToImageFilter.h"

namespace itk
{
template< class TImage>
class ImageFilterMultipleInputs : public ImageToImageFilter< TImage, TImage >
{
public:
  /** Standard class type alias. */
  using Self = ImageFilterMultipleInputs;
  using Superclass = ImageToImageFilter< TImage, TImage >;
  using Pointer = SmartPointer< Self >;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilterMultipleInputs, ImageToImageFilter);

  /** The image to be inpainted in regions where the mask is white.*/
  void SetInputImage(const TImage* image);

  /** The mask to be inpainted. White pixels will be inpainted, black pixels will be passed through to the output.*/
  void SetInputMask(const TImage* mask);
  
protected:
  ImageFilterMultipleInputs();
  ~ImageFilterMultipleInputs() override{}

  /** Does the real work. */
  void GenerateData() override;

private:
  ImageFilterMultipleInputs(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented

};
} //namespace ITK


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImageFilterMultipleInputs.hxx"
#endif


#endif // itkImageFilterMultipleInputs_h

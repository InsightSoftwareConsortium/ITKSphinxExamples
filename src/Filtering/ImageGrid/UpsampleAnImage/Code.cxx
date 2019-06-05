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
#include "itkIdentityTransform.h"
#include "itkBSplineInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"

#include <iostream>

int main( int argc, char * argv[] )
{
    if( argc != 5 )
    {
        std::cerr << "Usage: "
                  << std::endl
                  << argv[0]
                  << " inputImageFile outputImageFile nNewWidth nNewHeight"
                  << std::endl;

        return EXIT_FAILURE;
    }

    // Typedef's for pixel, image, reader and writer types
    using T_InputPixel = unsigned char;

    // Doesn't work for RGB pixels
    //using T_OutputPixel = unsigned char;
    //using T_InputPixel = itk::CovariantVector<unsigned char, 3>;
    //using T_OutputPixel = itk::CovariantVector<unsigned char, 3>;

    using T_Image = itk::Image<T_InputPixel, 2>;
    using T_Reader = itk::ImageFileReader<T_Image>;

    using T_WritePixel = unsigned char;
    using T_WriteImage = itk::Image<T_WritePixel, 2>;
    using T_Writer = itk::ImageFileWriter<T_WriteImage>;

    // Typedefs for the different (numerous!) elements of the "resampling"

    // Identity transform.
    // We don't want any transform on our image except rescaling which is not
    // specified by a transform but by the input/output spacing as we will see
    // later.
    // So no transform will be specified.
    using T_Transform = itk::IdentityTransform<double, 2>;

    // If ITK resampler determines there is something to interpolate which is
    // usually the case when upscaling (!) then we must specify the interpolation
    // algorithm. In our case, we want bicubic interpolation. One way to implement
    // it is with a third order b-spline. So the type is specified here and the
    // order will be specified with a method call later on.
    using T_Interpolator = itk::BSplineInterpolateImageFunction<T_Image, double, double>;

    // The resampler type itself.
    using T_ResampleFilter = itk::ResampleImageFilter<T_Image, T_Image>;


    // Prepare the reader and update it right away to know the sizes beforehand.

    T_Reader::Pointer pReader = T_Reader::New();
    pReader->SetFileName( argv[1] );
    pReader->Update();

    // Prepare the resampler.

    // Instantiate the transform and specify it should be the id transform.
    T_Transform::Pointer _pTransform = T_Transform::New();
    _pTransform->SetIdentity();

    // Instantiate the b-spline interpolator and set it as the third order
    // for bicubic.
    T_Interpolator::Pointer _pInterpolator = T_Interpolator::New();
    _pInterpolator->SetSplineOrder(3);

    // Instantiate the resampler. Wire in the transform and the interpolator.
    T_ResampleFilter::Pointer _pResizeFilter = T_ResampleFilter::New();
    _pResizeFilter->SetTransform(_pTransform);
    _pResizeFilter->SetInterpolator(_pInterpolator);

    // Set the output origin. You may shift the original image "inside" the
    // new image size by specifying something else than 0.0, 0.0 here.

    const double vfOutputOrigin[2]  = { 0.0, 0.0 };
    _pResizeFilter->SetOutputOrigin(vfOutputOrigin);

    //     Compute and set the output spacing
    //     Compute the output spacing from input spacing and old and new sizes.
    //
    //     The computation must be so that the following holds:
    //
    //     new width         old x spacing
    //     ----------   =   ---------------
    //     old width         new x spacing
    //
    //
    //     new height         old y spacing
    //    ------------  =   ---------------
    //     old height         new y spacing
    //
    //     So either we specify new height and width and compute new spacings (as
    //     we do here) or we specify new spacing and compute new height and width
    //     and computations that follows need to be modified a little (as it is
    //     done at step 2 there:
    //       http://itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM)
    //
    unsigned int nNewWidth = std::stoi(argv[3]);
    unsigned int nNewHeight = std::stoi(argv[4]);

    // Fetch original image size.
    const T_Image::RegionType& inputRegion =
            pReader->GetOutput()->GetLargestPossibleRegion();
    const T_Image::SizeType& vnInputSize = inputRegion.GetSize();
    unsigned int nOldWidth = vnInputSize[0];
    unsigned int nOldHeight = vnInputSize[1];

    // Fetch original image spacing.
    const T_Image::SpacingType& vfInputSpacing =
            pReader->GetOutput()->GetSpacing();
    // Will be {1.0, 1.0} in the usual
    // case.

    double vfOutputSpacing[2];
    vfOutputSpacing[0] = vfInputSpacing[0] * (double) nOldWidth / (double) nNewWidth;
    vfOutputSpacing[1] = vfInputSpacing[1] * (double) nOldHeight / (double) nNewHeight;

    // Set the output spacing. If you comment out the following line, the original
    // image will be simply put in the upper left corner of the new image without
    // any scaling.
    _pResizeFilter->SetOutputSpacing(vfOutputSpacing);

    // Set the output size as specified on the command line.

    itk::Size<2> vnOutputSize = { {nNewWidth, nNewHeight} };
    _pResizeFilter->SetSize(vnOutputSize);

    // Specify the input.

    _pResizeFilter->SetInput(pReader->GetOutput());

    // Write the result
    T_Writer::Pointer pWriter = T_Writer::New();
    pWriter->SetFileName(argv[2]);
    pWriter->SetInput(_pResizeFilter->GetOutput());
    pWriter->Update();

    return EXIT_SUCCESS;
}

import itk

Dimension = 2
PixelType = itk.UC
Double = itk.D
Float = itk.F
ImageType = itk.Image[PixelType, Dimension]

def main():
#   The transform that will map the fixed image into the moving image.
    TransformType = itk.TranslationTransform[Double, Dimension]

#   An optimizer is required to explore the parameter space of the transform
#   in search of optimal values of the metric.
    OptimizerType = itk.RegularStepGradientDescentOptimizer

#   The metric will compare how well the two images match each other. Metric
#   types are usually parameterized by the image types as it can be seen in
#   the following type declaration.
    MetricType = itk.MeanSquaresImageToImageMetric[ImageType, ImageType]

#   Finally, the type of the interpolator is declared. The interpolator will
#   evaluate the intensities of the moving image at non-grid positions.
    InterpolatorType = itk.LinearInterpolateImageFunction[ImageType, Double]

#   The registration method type is instantiated using the types of the
#   fixed and moving images. This class is responsible for interconnecting
#   all the components that we have described so far.
    RegistrationType = itk.ImageRegistrationMethod[ImageType, ImageType]

#   Create components
    metric = MetricType.New()
    transform = TransformType.New()
    optimizer = OptimizerType.New()
    interpolator = InterpolatorType.New()
    registration = RegistrationType.New()

#   Each component is now connected to the instance of the registration method.
    registration.SetMetric(metric)
    registration.SetOptimizer(optimizer)
    registration.SetTransform(transform)
    registration.SetInterpolator(interpolator)

#   Get the two images
    fixedImage = ImageType.New()
    movingImage = ImageType.New()

    CreateSphereImage(fixedImage)
    CreateEllipseImage(movingImage)

#   Write the two synthetic inputs
    itk.imwrite(fixedImage, "fixed.png")
    itk.imwrite(movingImage, "moving.png")
    
#   Set the registration inputs
    registration.SetFixedImage(fixedImage)
    registration.SetMovingImage(movingImage)

    registration.SetFixedImageRegion(fixedImage.GetLargestPossibleRegion())

#   Initialize the transform
    initialParameters = itk.OptimizerParameters[itk.D](transform.GetNumberOfParameters())

    initialParameters[0] = 0.0 # Initial offset along X
    initialParameters[1] = 0.0 # Initial offset along Y

    registration.SetInitialTransformParameters(initialParameters)

    optimizer.SetMaximumStepLength(4.00)
    optimizer.SetMinimumStepLength(0.01)

#   Set a stopping criterion
    optimizer.SetNumberOfIterations(200)

#   Connect an observer
#     surface = dict()
#     def print_iteration():
#         surface[tuple(optimizer.GetCurrentPosition())] = optimizer.GetValue()
#         print(surface)
    
#     optimizer.AddObserver(itk.IterationEvent(), print_iteration)
    
    
    try:
        registration.Update()
    except:
        print("ExceptionObject caught !")
        return 

#     The result of the registration process is an array of parameters that
#     defines the spatial transformation in an unique way. This final result is
#     obtained using the \code{GetLastTransformParameters()} method.

    finalParameters = registration.GetLastTransformParameters()

#     In the case of the \doxygen{TranslationTransform}, there is a
#     straightforward interpretation of the parameters.  Each element of the
#     array corresponds to a translation along one spatial dimension.

    TranslationAlongX = finalParameters[0]
    TranslationAlongY = finalParameters[1]

#     The optimizer can be queried for the actual number of iterations
#     performed to reach convergence.  The \code{GetCurrentIteration()}
#     method returns this value. A large number of iterations may be an
#     indication that the maximum step length has been set too small, which
#     is undesirable since it results in long computational times.

    numberOfIterations = optimizer.GetCurrentIteration()

#     The value of the image metric corresponding to the last set of parameters
#     can be obtained with the \code{GetValue()} method of the optimizer.

    bestValue = optimizer.GetValue()

#     Print out results
    print("Result = ")
    print(" Translation X = {}".format(TranslationAlongX))
    print(" Translation Y = {}".format(TranslationAlongY))
    print(" Iterations    = {}".format(numberOfIterations))
    print(" Metric value  = {}".format(bestValue))

#     It is common, as the last step of a registration task, to use the
#     resulting transform to map the moving image into the fixed image space.
#     This is easily done with the \doxygen{ResampleImageFilter}. Please
#     refer to Section~\ref{sec:ResampleImageFilter} for details on the use
#     of this filter.  First, a ResampleImageFilter type is instantiated
#     using the image types. It is convenient to use the fixed image type as
#     the output type since it is likely that the transformed moving image
#     will be compared with the fixed image.
    ResampleFilterType = itk.ResampleImageFilter[ImageType, ImageType]

#     A resampling filter is created and the moving image is connected as  its input.

    resampler = ResampleFilterType.New()
    resampler.SetInput(movingImage)

#     The Transform that is produced as output of the Registration method is
#     also passed as input to the resampling filter. Note the use of the
#     methods \code{GetOutput()} and \code{Get()}. This combination is needed
#     here because the registration method acts as a filter whose output is a
#     transform decorated in the form of a \doxygen{DataObject}. For details in
#     this construction you may want to read the documentation of the
#     \doxygen{DataObjectDecorator}.

    resampler.SetTransform(registration.GetOutput().Get())

#     As described in Section \ref{sec:ResampleImageFilter}, the
#     ResampleImageFilter requires additional parameters to be specified, in
#     particular, the spacing, origin and size of the output image. The default
#     pixel value is also set to a distinct gray level in order to highlight
#     the regions that are mapped outside of the moving image.

    resampler.SetSize(itk.size(fixedImage))
    resampler.SetOutputOrigin(fixedImage.GetOrigin())
    resampler.SetOutputSpacing(fixedImage.GetSpacing())
    resampler.SetOutputDirection(fixedImage.GetDirection())
    resampler.SetDefaultPixelValue(100)

#     The output of the filter is passed to a writer that will store the
#     image in a file. An \doxygen{CastImageFilter} is used to convert the
#     pixel type of the resampled image to the final type used by the
#     writer. The cast and writer filters are instantiated below.
    CastFilterType = itk.CastImageFilter[ImageType, ImageType]

    caster = CastFilterType.New()
    caster.SetInput(resampler.GetOutput())
    itk.imwrite(caster.GetOutput(), "outputPython.png")


#     The fixed image and the transformed moving image can easily be compared
#     using the \doxygen{SubtractImageFilter}. This pixel-wise filter computes
#     the difference between homologous pixels of its two input images.


    DifferenceFilterType = itk.SubtractImageFilter[
      ImageType,
      ImageType,
      ImageType]

    difference = DifferenceFilterType.New()
    difference.SetInput1( fixedImage )
    difference.SetInput2( resampler.GetOutput() )
    
    return 


def CreateEllipseImage(image):
    EllipseType = itk.EllipseSpatialObject[Dimension]

    SpatialObjectToImageFilterType = itk.SpatialObjectToImageFilter[itk.SpatialObject[2], ImageType]

    imageFilter = SpatialObjectToImageFilterType.New()

    size = itk.Size[Dimension]()
    size[0] = 100
    size[1] = 100

    imageFilter.SetSize(size)
    
    spacing = [1, 1]
    imageFilter.SetSpacing(spacing)
    
    ellipse = EllipseType.New()
    radiusArray = itk.Array[Float]()
    radiusArray.SetSize(Dimension)
    radiusArray[0] = 10
    radiusArray[1] = 20
    ellipse.SetRadiusInObjectSpace(radiusArray)

    TransformType = itk.AffineTransform[Double, Dimension]
    transform = TransformType.New()
    transform.SetIdentity()

    translation = itk.Vector[Float, Dimension]()
    translation[0] = 65
    translation[1] = 45
    transform.Translate(translation, False)

    ellipse.SetObjectToParentTransform(transform)

    imageFilter.SetInput(ellipse)

    ellipse.SetDefaultInsideValue(255)
    ellipse.SetDefaultOutsideValue(0)
    imageFilter.SetUseObjectValue(True)
    imageFilter.SetOutsideValue(0)

    imageFilter.Update()
    image.Graft(imageFilter.GetOutput())


def CreateSphereImage(image):
    EllipseType = itk.EllipseSpatialObject[Dimension]

    SpatialObjectToImageFilterType = itk.SpatialObjectToImageFilter[itk.SpatialObject[2], itk.Image[itk.UC,2]]

    imageFilter = SpatialObjectToImageFilterType.New()

    size = itk.Size[Dimension]()
    size[0] = 100
    size[1] = 100
    imageFilter.SetSize(size)
    
    spacing = [1, 1]
    imageFilter.SetSpacing(spacing)

    ellipse = EllipseType.New()
    radiusArray = itk.Array[Float]()
    radiusArray.SetSize(Dimension)
    radiusArray[0] = 10
    radiusArray[1] = 10
    ellipse.SetRadiusInObjectSpace(radiusArray)

    TransformType = itk.AffineTransform[Double, Dimension]
    transform = TransformType.New()
    transform.SetIdentity()

    translation =  itk.Vector[PixelType, Dimension]()
    translation[0] = 50
    translation[1] = 50
    transform.Translate(translation, False)

    ellipse.SetObjectToParentTransform(transform)

    imageFilter.SetInput(ellipse)

    ellipse.SetDefaultInsideValue(255)
    ellipse.SetDefaultOutsideValue(0)
    imageFilter.SetUseObjectValue(True)
    imageFilter.SetOutsideValue(0)
    
    imageFilter.Update()
    image.Graft(imageFilter.GetOutput())

if __name__ == "__main__":
    main()
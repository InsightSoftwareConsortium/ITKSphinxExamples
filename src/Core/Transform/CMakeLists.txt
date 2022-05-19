add_example(CopyANonCompositeTransform)
add_example(CopyACompositeTransform)

add_example(TranslateImage)
compare_to_baseline(
  EXAMPLE_NAME TranslateImage
  BASELINE_PREFIX OutputBaseline
)

add_example(ApplyAffineTransformFromHomogeneousMatrixAndResample)
compare_to_baseline(
  EXAMPLE_NAME ApplyAffineTransformFromHomogeneousMatrixAndResample
  BASELINE_PREFIX OutputBaseline
)

add_example(ScaleAnImage)
compare_to_baseline(EXAMPLE_NAME ScaleAnImage
  BASELINE_PREFIX ScaleAnImageOutput
  )

add_example(TranslateAVectorImage)
add_example(CartesianToAzimuthElevation)

add_example(GlobalRegistrationTwoImagesAffine)
compare_to_baseline(EXAMPLE_NAME GlobalRegistrationTwoImagesAffine
  BASELINE_PREFIX
    fixed
    moving
    output
  )

add_example(MutualInformationAffine)
compare_to_baseline(EXAMPLE_NAME MutualInformationAffine
  BASELINE_PREFIX
    OutputBaseline
  )

add_example(GlobalRegistrationTwoImagesBSpline)
compare_to_baseline(EXAMPLE_NAME GlobalRegistrationTwoImagesBSpline
  BASELINE_PREFIX GlobalRegistrationTwoImagesBSpline
  )

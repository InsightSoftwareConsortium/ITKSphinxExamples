
add_example(MultiplyKernelWithAnImageAtLocation)
compare_to_baseline(EXAMPLE_NAME MultiplyKernelWithAnImageAtLocation
  BASELINE_PREFIX OutputBaseline
  )

add_example(GaussianBlurImageFunction)
compare_to_baseline(EXAMPLE_NAME GaussianBlurImageFunction
  BASELINE_PREFIX OutputBaseline
  )

add_example(ComputeMedianOfImageAtPixel)
compare_to_baseline(EXAMPLE_NAME ComputeMedianOfImageAtPixel
  BASELINE_PREFIX OutputBaseline
  )

add_example(ResampleSegmentedImage)
compare_to_baseline(EXAMPLE_NAME ResampleSegmentedImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(LinearlyInterpolatePositionInImage)
compare_to_baseline(EXAMPLE_NAME LinearlyInterpolatePositionInImage
  BASELINE_PREFIX OutputBaseline
  )

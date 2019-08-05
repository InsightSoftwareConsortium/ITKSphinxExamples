add_example(MultiplyKernelWithAnImageAtLocation)

add_example(ComputeMedianOfImageAtPixel)
compare_to_baseline(EXAMPLE_NAME ComputeMedianOfImageAtPixel
  BASELINE_PREFIX ComputeMedianOfImageAtPixel
  )

add_example(LinearlyInterpolatePositionInImage)

if(ENABLE_QUICKVIEW)

# TODO Fix build errors
add_example(ResampleSegmentedImage)

endif()
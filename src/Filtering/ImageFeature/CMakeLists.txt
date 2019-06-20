add_example(ComputeLaplacian)
compare_to_baseline(EXAMPLE_NAME ComputeLaplacian BASELINE_PREFIX OutputBaseline)

add_example(DetectEdgesWithCannyFilter)
compare_to_baseline(EXAMPLE_NAME DetectEdgesWithCannyFilter BASELINE_PREFIX OutputBaseline)

add_example(SobelEdgeDetectionImageFilter)
compare_to_baseline(EXAMPLE_NAME SobelEdgeDetectionImageFilter BASELINE_PREFIX OutputBaseline)

add_example(LaplacianRecursiveGaussianImageFilter)
compare_to_baseline(EXAMPLE_NAME LaplacianRecursiveGaussianImageFilter BASELINE_PREFIX OutputBaseline)

add_example(SegmentBloodVessels)
compare_to_baseline(EXAMPLE_NAME SegmentBloodVessels BASELINE_PREFIX OutputBaseline OPTIONS --tolerance-number-of-pixels 10)

add_example(RequestedRegion)
compare_to_baseline(EXAMPLE_NAME RequestedRegion
  BASELINE_PREFIX OutputBaseline
  )

add_example(DerivativeImage)
compare_to_baseline(EXAMPLE_NAME DerivativeImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(SharpenImage)
compare_to_baseline(EXAMPLE_NAME SharpenImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(FindZeroCrossings)
compare_to_baseline(EXAMPLE_NAME FindZeroCrossings
  BASELINE_PREFIX OutputBaseline
  )

add_example(ZeroCrossingBasedEdgeDecor)
compare_to_baseline(EXAMPLE_NAME ZeroCrossingBasedEdgeDecor
  BASELINE_PREFIX OutputBaseline
  )

add_example(BilateralFilterAnImage)
compare_to_baseline(EXAMPLE_NAME BilateralFilterAnImage
  BASELINE_PREFIX OutputBaseline
  )

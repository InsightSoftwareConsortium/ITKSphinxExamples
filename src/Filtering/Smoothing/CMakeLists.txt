add_example( ApplyMeanFilter )
compare_to_baseline( EXAMPLE_NAME ApplyMeanFilter BASELINE_PREFIX OutputBaseline )
add_example( ApplyMedianFilter )
compare_to_baseline( EXAMPLE_NAME ApplyMedianFilter BASELINE_PREFIX OutputBaseline )
add_example( MedianFilteringOfAnRGBImage )
compare_to_baseline( EXAMPLE_NAME MedianFilteringOfAnRGBImage
  BASELINE_PREFIX OutputBaseline OPTIONS --tolerance-intensity 2.0e1 )
add_example( SmoothWithRecursiveGaussian )
compare_to_baseline( EXAMPLE_NAME SmoothWithRecursiveGaussian BASELINE_PREFIX OutputBaseline )

add_example(BlurringAnImageUsingABinomialKernel)
compare_to_baseline( EXAMPLE_NAME BlurringAnImageUsingABinomialKernel BASELINE_PREFIX OutputBaseline )

if(ENABLE_QUICKVIEW)

add_example(FindHigherDerivativesOfImage)
compare_to_baseline(EXAMPLE_NAME FindHigherDerivativesOfImage
  BASELINE_PREFIX FindHigherDerivativesOfImage
  )

add_example(SmoothImageWithDiscreteGaussianFilter)
compare_to_baseline(EXAMPLE_NAME SmoothImageWithDiscreteGaussianFilter
  BASELINE_PREFIX SmoothImageWithDiscreteGaussianFilter
  )

endif()
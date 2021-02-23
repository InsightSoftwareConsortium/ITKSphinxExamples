add_example(NormalizedCorrelationOfMaskedImage)
compare_to_baseline(EXAMPLE_NAME NormalizedCorrelationOfMaskedImage
  BASELINE_PREFIX correlation
  )

add_example(NormalizedCorrelationUsingFFT)
compare_to_baseline(EXAMPLE_NAME NormalizedCorrelationUsingFFT
  BASELINE_PREFIX correlation
  )

add_example(NormalizedCorrelationUsingFFTWithMaskImages)
compare_to_baseline(EXAMPLE_NAME NormalizedCorrelationUsingFFTWithMaskImages
  BASELINE_PREFIX correlation
  )

add_example(ConvolveImageWithKernel)
compare_to_baseline(EXAMPLE_NAME ConvolveImageWithKernel
  BASELINE_PREFIX ConvolveImageWithKernel
  )

# TODO:  Fix building of ColorNormalizedCorrelation example
# add_example(ColorNormalizedCorrelation)
#compare_to_baseline(EXAMPLE_NAME ColorNormalizedCorrelation
#  BASELINE_PREFIX OutputBaseline
#  )

# TODO: Fix build errors for NormalizedCorrelation
#add_example(NormalizedCorrelation)
#compare_to_baseline(EXAMPLE_NAME NormalizedCorrelation
#  BASELINE_PREFIX correlation patch
#  )
#===========================================

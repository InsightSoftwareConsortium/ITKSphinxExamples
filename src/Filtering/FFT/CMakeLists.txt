add_example( FilterImageInFourierDomain )
compare_to_baseline(
  EXAMPLE_NAME FilterImageInFourierDomain
  BASELINE_PREFIX OutputBaseline
  OPTIONS --tolerance-intensity 5
)

add_example( ComputeImageSpectralDensity )
compare_to_baseline(
  EXAMPLE_NAME ComputeImageSpectralDensity
  BASELINE_PREFIX OutputBaseline
  OPTIONS --tolerance-intensity 5
)

add_example( ComputeForwardFFT )
compare_to_baseline(
  EXAMPLE_NAME ComputeForwardFFT
  BASELINE_PREFIX OutputBaseline
  OPTIONS --tolerance-intensity 5
)

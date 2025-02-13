add_example(ComputeFFTInOneDimension)
compare_to_baseline(
  PYTHON_ONLY
  EXAMPLE_NAME ComputeFFTInOneDimension
  TEST_NAME ComputeFFTInOneDimensionModulusBaselineComparison
  BASELINE_PREFIX MouseLiver1DFFTModulusOutputBaseline
)
compare_to_baseline(
  PYTHON_ONLY
  EXAMPLE_NAME ComputeFFTInOneDimension
  TEST_NAME ComputeFFTInOneDimensionPhaseBaselineComparison
  BASELINE_PREFIX MouseLiver1DFFTPhaseOutputBaseline
)

compare_to_baseline(
  EXAMPLE_NAME FilterImageInFourierDomain
  BASELINE_PREFIX OutputBaseline
  OPTIONS --tolerance-intensity 5
)

add_example(ComputeImageSpectralDensity)
compare_to_baseline(
  EXAMPLE_NAME ComputeImageSpectralDensity
  BASELINE_PREFIX OutputBaseline
  OPTIONS --tolerance-intensity 5
)

add_example(ComputeForwardFFT)
compare_to_baseline(
  EXAMPLE_NAME ComputeForwardFFT
  TEST_NAME ComputeForwardFFTTestRealBaselineComparison
  BASELINE_PREFIX OutputRealBaseline
  OPTIONS --tolerance-intensity 5
  TEST_IMAGE OutputReal.mha
)

compare_to_baseline(
  EXAMPLE_NAME ComputeForwardFFT
  TEST_NAME ComputeForwardFFTTestComplexBaselineComparison
  BASELINE_PREFIX OutputComplexBaseline
  OPTIONS --tolerance-intensity 5
  TEST_IMAGE OutputComplex.mha
)

compare_to_baseline(
  EXAMPLE_NAME ComputeForwardFFT
  TEST_NAME ComputeForwardFFTTestModulusBaselineComparison
  BASELINE_PREFIX OutputModulusBaseline
  OPTIONS --tolerance-intensity 5
  TEST_IMAGE OutputModulus.mha
)

add_example(ComputeInverseFFTOfImage)
compare_to_baseline(EXAMPLE_NAME ComputeInverseFFTOfImage
  BASELINE_PREFIX ComputeInverseFFTOfImage
  )

add_example( CastAnImageToAnotherType )
compare_to_baseline( EXAMPLE_NAME CastAnImageToAnotherType BASELINE_PREFIX OutputBaseline )

add_example(ApplyKernelToEveryPixel)
compare_to_baseline(EXAMPLE_NAME ApplyKernelToEveryPixel
  BASELINE_PREFIX output
  )

add_example(ApplyKernelToEveryPixelInNonZeroImage)
compare_to_baseline(EXAMPLE_NAME ApplyKernelToEveryPixelInNonZeroImage
  BASELINE_PREFIX output
  )

add_example(CustomOperationToCorrespondingPixelsInTwoImages)

add_example(ComputeLocalNoise)
compare_to_baseline(EXAMPLE_NAME ComputeLocalNoise
  BASELINE_PREFIX output
  )

# TODO Fix example for clean build
add_example(PredefinedOperationToCorrespondingPixelsInTwoImages)

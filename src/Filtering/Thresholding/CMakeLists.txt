add_example( ThresholdAnImageUsingOtsu )
compare_to_baseline( EXAMPLE_NAME ThresholdAnImageUsingOtsu BASELINE_PREFIX OutputBaseline)

add_example( ThresholdAnImageUsingBinary )
compare_to_baseline( EXAMPLE_NAME ThresholdAnImageUsingBinary BASELINE_PREFIX OutputBaseline)

add_example( ThresholdAnImage )
compare_to_baseline( EXAMPLE_NAME ThresholdAnImage BASELINE_PREFIX OutputBaseline )

add_example(DemonstrateThresholdAlgorithms)
compare_to_baseline(EXAMPLE_NAME DemonstrateThresholdAlgorithms
  BASELINE_PREFIX OutputBaseline
  )

add_example(SeparateGroundUsingOtsu)
compare_to_baseline(EXAMPLE_NAME SeparateGroundUsingOtsu
  BASELINE_PREFIX OutputBaseline
  )

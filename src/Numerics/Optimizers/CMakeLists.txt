
add_example(AmoebaOptimizer)
compare_to_baseline(EXAMPLE_NAME AmoebaOptimizer
  BASELINE_PREFIX OutputBaseline
  )

add_example(LevenbergMarquardtOptimization)
compare_to_baseline(EXAMPLE_NAME LevenbergMarquardtOptimization
  BASELINE_PREFIX OutputBaseline
  )

add_example(ExhaustiveOptimizer)
compare_to_baseline(EXAMPLE_NAME ExhaustiveOptimizer
  BASELINE_PREFIX OutputBaseline
  )

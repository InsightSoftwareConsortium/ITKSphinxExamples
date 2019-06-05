
add_example(BinaryMinMaxCurvatureFlow)
compare_to_baseline(EXAMPLE_NAME BinaryMinMaxCurvatureFlow
  BASELINE_PREFIX OutputBaseline
  )

add_example(SmoothImageUsingCurvatureFlow)
compare_to_baseline(EXAMPLE_NAME SmoothImageUsingCurvatureFlow
  BASELINE_PREFIX OutputBaseline
  )

add_example(SmoothRGBImageUsingCurvatureFlow)
compare_to_baseline(EXAMPLE_NAME SmoothRGBImageUsingCurvatureFlow
  BASELINE_PREFIX OutputBaseline
  )

add_example(SmoothImageUsingMinMaxCurvatureFlow)
compare_to_baseline(EXAMPLE_NAME SmoothImageUsingMinMaxCurvatureFlow
  BASELINE_PREFIX OutputBaseline
  )

add_example(SmoothRGBImageUsingMinMaxCurvatureFlow)
compare_to_baseline(EXAMPLE_NAME SmoothRGBImageUsingMinMaxCurvatureFlow
  BASELINE_PREFIX OutputBaseline
  )

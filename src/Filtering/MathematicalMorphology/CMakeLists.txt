add_example( CreateABinaryBallStructuringElement )

add_example( DilateAGrayscaleImage )
compare_to_baseline( EXAMPLE_NAME DilateAGrayscaleImage BASELINE_PREFIX OutputBaseline )

add_example( ErodeAGrayscaleImage )
compare_to_baseline( EXAMPLE_NAME ErodeAGrayscaleImage BASELINE_PREFIX OutputBaseline )

add_example(RegionalMinimal)
compare_to_baseline(EXAMPLE_NAME RegionalMinimal
  BASELINE_PREFIX OutputBaseline
  )

add_example(RegionalMaximal)
compare_to_baseline(EXAMPLE_NAME RegionalMaximal
  BASELINE_PREFIX OutputBaseline
  )

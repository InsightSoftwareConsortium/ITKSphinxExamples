add_example( PerformMultiModalityRegistrationWithMutualInformation )
compare_to_baseline( EXAMPLE_NAME PerformMultiModalityRegistrationWithMutualInformation BASELINE_PREFIX OutputBaseline
  OPTIONS LABELS RUNS_LONG )

add_example( Perform2DTranslationRegistrationWithMeanSquares )
compare_to_baseline( EXAMPLE_NAME Perform2DTranslationRegistrationWithMeanSquares BASELINE_PREFIX OutputBaseline )

add_example(MultiresolutionPyramidFromImage)
compare_to_baseline(EXAMPLE_NAME MultiresolutionPyramidFromImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ComputeMeanSquareBetweenTwoImages)
compare_to_baseline(EXAMPLE_NAME ComputeMeanSquareBetweenTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(RegisterImageToAnotherUsingLandmarks)
compare_to_baseline(EXAMPLE_NAME RegisterImageToAnotherUsingLandmarks
  BASELINE_PREFIX OutputBaseline
  )

add_example(GlobalRegistrationOfTwoImages)
compare_to_baseline(EXAMPLE_NAME GlobalRegistrationOfTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(MutualInformation)
compare_to_baseline(EXAMPLE_NAME MutualInformation
  BASELINE_PREFIX OutputBaseline
  )

add_example(WatchRegistration)
compare_to_baseline(EXAMPLE_NAME WatchRegistration
  BASELINE_PREFIX OutputBaseline
  )

add_example(MatchFeaturePoints)
compare_to_baseline(EXAMPLE_NAME MatchFeaturePoints
  BASELINE_PREFIX OutputBaseline
  )

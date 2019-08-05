add_example( PerformMultiModalityRegistrationWithMutualInformation )
compare_to_baseline( EXAMPLE_NAME PerformMultiModalityRegistrationWithMutualInformation BASELINE_PREFIX OutputBaseline
  OPTIONS LABELS RUNS_LONG )

if(ITKV4_COMPATIBILITY)
  add_example( Perform2DTranslationRegistrationWithMeanSquares )
  compare_to_baseline( EXAMPLE_NAME Perform2DTranslationRegistrationWithMeanSquares BASELINE_PREFIX OutputBaseline )
endif()

add_example(MultiresolutionPyramidFromImage)
compare_to_baseline(EXAMPLE_NAME MultiresolutionPyramidFromImage
  BASELINE_PREFIX output_0 output_1 output_2 output_3
  )

add_example(ComputeMeanSquareBetweenTwoImages)

add_example(RegisterImageToAnotherUsingLandmarks)
compare_to_baseline(EXAMPLE_NAME RegisterImageToAnotherUsingLandmarks
  BASELINE_PREFIX output
  )

add_example(GlobalRegistrationOfTwoImages)
compare_to_baseline(EXAMPLE_NAME GlobalRegistrationOfTwoImages
  BASELINE_PREFIX output
  )

add_example(MutualInformation)
compare_to_baseline(EXAMPLE_NAME MutualInformation
  BASELINE_PREFIX output
  )

if(ENABLE_QUICKVIEW)
add_example(WatchRegistration)
compare_to_baseline(EXAMPLE_NAME WatchRegistration
  BASELINE_PREFIX OutputBaseline
  )
endif()

# TODO: Fix build errors
# add_example(MatchFeaturePoints)
#compare_to_baseline(EXAMPLE_NAME MatchFeaturePoints
#  BASELINE_PREFIX OutputBaseline
#  )

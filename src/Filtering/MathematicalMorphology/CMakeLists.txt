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

add_example(ValuedRegionalMaximaImage)
compare_to_baseline(EXAMPLE_NAME ValuedRegionalMaximaImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ValuedRegionalMinimalImage)
compare_to_baseline(EXAMPLE_NAME ValuedRegionalMinimalImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ErodeBinaryImageUsingFlatStruct)
compare_to_baseline(EXAMPLE_NAME ErodeBinaryImageUsingFlatStruct
  BASELINE_PREFIX OutputBaseline
  )

add_example(GenerateStructureElementsWithAccurateArea)
compare_to_baseline(EXAMPLE_NAME GenerateStructureElementsWithAccurateArea
  BASELINE_PREFIX OutputBaseline
  )

add_example( CreateABinaryBallStructuringElement )

add_example( DilateAGrayscaleImage )
compare_to_baseline( EXAMPLE_NAME DilateAGrayscaleImage BASELINE_PREFIX OutputBaseline )

add_example( ErodeAGrayscaleImage )
compare_to_baseline( EXAMPLE_NAME ErodeAGrayscaleImage BASELINE_PREFIX OutputBaseline )

add_example(RegionalMinimal)
compare_to_baseline(EXAMPLE_NAME RegionalMinimal
  BASELINE_PREFIX output
  )

add_example(RegionalMaximal)
compare_to_baseline(EXAMPLE_NAME RegionalMaximal
  BASELINE_PREFIX intensityblobs maximal
  )

add_example(ValuedRegionalMaximaImage)
compare_to_baseline(EXAMPLE_NAME ValuedRegionalMaximaImage
  BASELINE_PREFIX intensityblobs maximal
  )

add_example(ValuedRegionalMinimalImage)
compare_to_baseline(EXAMPLE_NAME ValuedRegionalMinimalImage
  BASELINE_PREFIX output
  )

add_example(ErodeBinaryImageUsingFlatStruct)
compare_to_baseline(EXAMPLE_NAME ErodeBinaryImageUsingFlatStruct
  BASELINE_PREFIX ErodeBinaryImageUsingFlatStruct
  )

add_example(GenerateStructureElementsWithAccurateArea)

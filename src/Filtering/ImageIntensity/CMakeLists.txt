add_example( RescaleAnImage )
compare_to_baseline( EXAMPLE_NAME RescaleAnImage BASELINE_PREFIX OutputBaseline )

add_example( ApplySinImageFilter )
compare_to_baseline( EXAMPLE_NAME ApplySinImageFilter BASELINE_PREFIX OutputBaseline OPTIONS --tolerance-intensity 1.0e-6 )

add_example( ApplyCosImageFilter )
compare_to_baseline( EXAMPLE_NAME ApplyCosImageFilter BASELINE_PREFIX OutputBaseline OPTIONS --tolerance-intensity 1.0e-6 )

add_example( ApplyAtanImageFilter )
compare_to_baseline( EXAMPLE_NAME ApplyAtanImageFilter BASELINE_PREFIX OutputBaseline )

add_example( ConvertRGBImageToGrayscaleImage )
compare_to_baseline( EXAMPLE_NAME ConvertRGBImageToGrayscaleImage BASELINE_PREFIX OutputBaseline )

add_example( MultiplyImageByScalar )
compare_to_baseline( EXAMPLE_NAME MultiplyImageByScalar BASELINE_PREFIX OutputBaseline )

add_example( ApplyExpNegativeImageFilter )
compare_to_baseline( EXAMPLE_NAME ApplyExpNegativeImageFilter BASELINE_PREFIX OutputBaseline )

add_example( ComputeSigmoid )
compare_to_baseline( EXAMPLE_NAME ComputeSigmoid BASELINE_PREFIX OutputBaseline )

add_example( MultiplyTwoImages )
compare_to_baseline( EXAMPLE_NAME MultiplyTwoImages BASELINE_PREFIX OutputBaseline )

add_example(PixelDivisionOfTwoImages)
compare_to_baseline(EXAMPLE_NAME PixelDivisionOfTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(ScalePixelSumToConstant)
compare_to_baseline(EXAMPLE_NAME ScalePixelSumToConstant
  BASELINE_PREFIX OutputBaseline
  )

add_example(AddConstantToEveryPixel)
compare_to_baseline(EXAMPLE_NAME AddConstantToEveryPixel
  BASELINE_PREFIX OutputBaseline
  )

add_example(AddTwoImages)
compare_to_baseline(EXAMPLE_NAME AddTwoImages
  BASELINE_PREFIX OutputBaseline
  )

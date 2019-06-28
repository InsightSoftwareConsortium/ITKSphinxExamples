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

add_example(SubtractConstantFromEveryPixel)
compare_to_baseline(EXAMPLE_NAME SubtractConstantFromEveryPixel
  BASELINE_PREFIX OutputBaseline
  )

add_example(SquareEveryPixel)
compare_to_baseline(EXAMPLE_NAME SquareEveryPixel
  BASELINE_PREFIX OutputBaseline
  )

add_example(TransformVectorValuedImagePixels)
compare_to_baseline(EXAMPLE_NAME TransformVectorValuedImagePixels
  BASELINE_PREFIX OutputBaseline
  )

add_example(IntensityWindowing)
compare_to_baseline(EXAMPLE_NAME IntensityWindowing
  BASELINE_PREFIX OutputBaseline
  )

add_example(SetOutputPixelToMax)
compare_to_baseline(EXAMPLE_NAME SetOutputPixelToMax
  BASELINE_PREFIX OutputBaseline
  )

add_example(SetOutputPixelToMin)
compare_to_baseline(EXAMPLE_NAME SetOutputPixelToMin
  BASELINE_PREFIX OutputBaseline
  )

add_example(BinaryANDTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryANDTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(BinaryORTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryORTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(BinaryXORTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryXORTwoImages
  BASELINE_PREFIX OutputBaseline
  )

add_example(AbsValueOfImage)
compare_to_baseline(EXAMPLE_NAME AbsValueOfImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(InvertImage)
compare_to_baseline(EXAMPLE_NAME InvertImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(MaskImage)
compare_to_baseline(EXAMPLE_NAME MaskImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(InverseOfMaskToImage)
compare_to_baseline(EXAMPLE_NAME InverseOfMaskToImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(NormalizeImage)
compare_to_baseline(EXAMPLE_NAME NormalizeImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CastImageToAnotherTypeButClampToOutput)
compare_to_baseline(EXAMPLE_NAME CastImageToAnotherTypeButClampToOutput
  BASELINE_PREFIX OutputBaseline
  )

add_example(ComputerMagInVectorImageToMakeMagImage)
compare_to_baseline(EXAMPLE_NAME ComputerMagInVectorImageToMakeMagImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ExtractComponentOfVectorImage)
compare_to_baseline(EXAMPLE_NAME ExtractComponentOfVectorImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ComputeEdgePotential)
compare_to_baseline(EXAMPLE_NAME ComputeEdgePotential
  BASELINE_PREFIX OutputBaseline
  )

if(ENABLE_QUICKVIEW)

add_example(AddTwoImages)
  compare_to_baseline(EXAMPLE_NAME AddTwoImages
    BASELINE_PREFIX OutputBaseline
  )

add_example(SubtractTwoImages)
compare_to_baseline(EXAMPLE_NAME SubtractTwoImages
  BASELINE_PREFIX OutputBaseline
  )

endif()


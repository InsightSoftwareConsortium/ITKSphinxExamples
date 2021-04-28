add_example( RescaleIntensity )
compare_to_baseline( EXAMPLE_NAME RescaleIntensity BASELINE_PREFIX OutputBaseline )

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
  BASELINE_PREFIX PixelDivisionOfTwoImages
  )

add_example(ScalePixelSumToConstant)

add_example(AddConstantToEveryPixel)
compare_to_baseline(EXAMPLE_NAME AddConstantToEveryPixel
  BASELINE_PREFIX output
  )

add_example(SubtractConstantFromEveryPixel)
compare_to_baseline(EXAMPLE_NAME SubtractConstantFromEveryPixel
  BASELINE_PREFIX SubtractConstantFromEveryPixel
  )

add_example(SquareEveryPixel)
compare_to_baseline(EXAMPLE_NAME SquareEveryPixel
  BASELINE_PREFIX SquareEveryPixel
  )

add_example(TransformVectorValuedImagePixels)
compare_to_baseline(EXAMPLE_NAME TransformVectorValuedImagePixels
  BASELINE_PREFIX TransformVectorValuedImagePixels
  )

add_example(IntensityWindowing)
compare_to_baseline(EXAMPLE_NAME IntensityWindowing
  BASELINE_PREFIX IntensityWindowing
  )

add_example(CompareTwoImagesAndSetOutputPixelToMax)
add_example(CompareTwoImagesAndSetOutputPixelToMin)

add_example(BinaryANDTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryANDTwoImages
  BASELINE_PREFIX BinaryANDTwoImages
  )

add_example(BinaryORTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryORTwoImages
  BASELINE_PREFIX BinaryORTwoImages
  )

add_example(BinaryXORTwoImages)
compare_to_baseline(EXAMPLE_NAME BinaryXORTwoImages
  BASELINE_PREFIX BinaryXORTwoImages
  )

add_example(InverseOfMaskToImage)
compare_to_baseline(EXAMPLE_NAME InverseOfMaskToImage
  BASELINE_PREFIX InverseOfMaskToImage
  )

add_example(CastImageToAnotherTypeButClampToOutput)

add_example(ComputerMagInVectorImageToMakeMagImage)
compare_to_baseline(EXAMPLE_NAME ComputerMagInVectorImageToMakeMagImage
  BASELINE_PREFIX ComputerMagInVectorImageToMakeMagImage
  )

add_example(ExtractComponentOfVectorImage)
add_example(ComputeEdgePotential)

add_example(AbsValueOfImage)
compare_to_baseline(EXAMPLE_NAME AbsValueOfImage
        BASELINE_PREFIX AbsValueOfImage
        )

add_example(NormalizeImage)
compare_to_baseline(EXAMPLE_NAME NormalizeImage
        BASELINE_PREFIX NormalizeImage
        )

add_example(InvertImage)
compare_to_baseline(EXAMPLE_NAME InvertImage
        BASELINE_PREFIX InvertImage
        )

add_example(MaskImage)
compare_to_baseline(EXAMPLE_NAME MaskImage
        BASELINE_PREFIX MaskImage
        )

if(VTK_DIR)

add_example(AddTwoImages)
compare_to_baseline(EXAMPLE_NAME AddTwoImages
        BASELINE_PREFIX AddTwoImages
        )

add_example(SubtractTwoImages)
compare_to_baseline(EXAMPLE_NAME SubtractTwoImages
        BASELINE_PREFIX SubtractTwoImages
        )

endif()

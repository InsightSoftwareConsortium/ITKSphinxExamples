add_example(ConvertAnitkImageTovtkImageData)
add_example(ConvertAnRGBitkImageTovtkImageData)
add_example(ConvertvtkImageDataToAnitkImage)
add_example(ConvertRGBvtkImageDataToAnitkImage)

if(ENABLE_QUICKVIEW)

add_example(VTKImageToITKImage)
compare_to_baseline(EXAMPLE_NAME VTKImageToITKImage
  BASELINE_PREFIX OutputBaseline
  )

endif()

add_example(ConvertAnitkImageTovtkImageData)
add_example(ConvertAnRGBitkImageTovtkImageData)
add_example(ConvertvtkImageDataToAnitkImage)
add_example(ConvertRGBvtkImageDataToAnitkImage)

if(ENABLE_QUICKVIEW)
  add_example(VTKImageToITKImage)
  #TODO: Save output ITK image and then use it to compare to baseline
  #compare_to_baseline(EXAMPLE_NAME VTKImageToITKImage
  #  BASELINE_PREFIX OutputBaseline
  #  )
endif()

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

if(ITK_VERSION_MAJOR LESS 5)
add_example(VisualizeEvolvingDense2DLevelSetAsElevationMap)
add_example(VisualizeEvolvingDense2DLevelSetZeroSet)
add_example(VisualizeStaticDense2DLevelSetAsElevationMap)
add_example(VisualizeStaticDense2DLevelSetZeroSet)
add_example(VisualizeStaticWhitaker2DLevelSetLayers)
add_example(VisualizeStaticShi2DLevelSetLayers)
add_example(VisualizeStaticMalcolm2DLevelSetLayers)
endif()

endif()


add_example(ResampleRGBImage)
compare_to_baseline(EXAMPLE_NAME ResampleRGBImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ResampleITKVectorImage)
compare_to_baseline(EXAMPLE_NAME ResampleITKVectorImage
  BASELINE_PREFIX OutputBaseline
  )

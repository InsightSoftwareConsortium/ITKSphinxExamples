add_example(ReadAnImage)
add_example(WriteAnImage)
add_example(CreateAListOfFileNames)

add_example(ConvertFileFormats)
compare_to_baseline(EXAMPLE_NAME ConvertFileFormats BASELINE_PREFIX OutputBaseline)

add_example(ReadUnknownImageType)

# IO Factories
get_property(_compile_defs DIRECTORY PROPERTY COMPILE_DEFINITIONS)
list(REMOVE_ITEM _compile_defs ITK_IO_FACTORY_REGISTER_MANAGER)
set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS ${_compile_defs})

add_example(RegisterIOFactories)

add_example(GenerateSlicesFromVolume)
compare_to_baseline(TEST_NAME GenerateSlicesFromVolumeBaselineComparisonSlice20
  EXAMPLE_NAME GenerateSlicesFromVolume
  BASELINE_PREFIX Output-20Baseline
  )
compare_to_baseline(TEST_NAME GenerateSlicesFromVolumeBaselineComparisonSlice30
  EXAMPLE_NAME GenerateSlicesFromVolume
  BASELINE_PREFIX Output-30Baseline
  )

add_example(ProcessImageChunks)
compare_to_baseline(
  EXAMPLE_NAME ProcessImageChunks
  BASELINE_PREFIX OutputBaseline
  TEST_IMAGE Output.mha
  )

add_example(ConvertImageToAnotherType)

add_example( ReadWriteAnRGBImage )
compare_to_baseline(
  EXAMPLE_NAME ReadWriteAnRGBImage
  BASELINE_PREFIX OutputBaseline
  TEST_IMAGE Output.png
  )


#TODO: When example has valid input, uncomment below
#add_example(Create3DFromSeriesOf2D)
#compare_to_baseline(EXAMPLE_NAME Create3DFromSeriesOf2D
#  BASELINE_PREFIX OutputBaseline
#  )

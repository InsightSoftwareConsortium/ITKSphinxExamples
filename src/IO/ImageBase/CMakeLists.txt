add_example( ReadAnImage )
add_example( WriteAnImage )
add_example( CreateAListOfFileNames )

add_example( ConvertFileFormats )
compare_to_baseline( EXAMPLE_NAME ConvertFileFormats BASELINE_PREFIX OutputBaseline )

add_example( ReadUnknownImageType )

# IO Factories
get_property( _compile_defs DIRECTORY PROPERTY COMPILE_DEFINITIONS )
list( REMOVE_ITEM _compile_defs ITK_IO_FACTORY_REGISTER_MANAGER )
set_property( DIRECTORY PROPERTY COMPILE_DEFINITIONS ${_compile_defs} )

add_example( RegisterIOFactories )

add_example( GenerateSlicesFromVolume )
compare_to_baseline( TEST_NAME GenerateSlicesFromVolumeBaselineComparisonSlice20
  EXAMPLE_NAME GenerateSlicesFromVolume
  BASELINE_PREFIX Output-20Baseline
  )
compare_to_baseline( TEST_NAME GenerateSlicesFromVolumeBaselineComparisonSlice30
  EXAMPLE_NAME GenerateSlicesFromVolume
  BASELINE_PREFIX Output-30Baseline
  )

add_example(ConvertImageToAnotherType)
compare_to_baseline(EXAMPLE_NAME ConvertImageToAnotherType
  BASELINE_PREFIX OutputBaseline
  )

add_example(Creade3DFromSeriesOf2D)
compare_to_baseline(EXAMPLE_NAME Creade3DFromSeriesOf2D
  BASELINE_PREFIX OutputBaseline
  )

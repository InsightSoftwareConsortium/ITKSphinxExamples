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

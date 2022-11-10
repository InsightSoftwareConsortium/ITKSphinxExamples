set(IO_MODULES
  ImageBase
  Mesh
  TIFF
  GDCM
  TransformBase
  TransformFactory
)

# Add subdirectories with corresponding ITK module names
add_subdirectory_if_module_enabled(ImageBase ITKIOImageBase)
add_subdirectory_if_module_enabled(Mesh ITKIOMesh)
add_subdirectory_if_module_enabled(TIFF ITKIOTIFF)
add_subdirectory_if_module_enabled(GDCM ITKGDCM)
add_subdirectory_if_module_enabled(TransformBase)
add_subdirectory_if_module_enabled(TransformFactory)

foreach(_module ${IO_MODULES})
  add_module_archives(${_module})
endforeach()

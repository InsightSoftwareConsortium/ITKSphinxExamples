ExternalProject_Add( ITKDoxygenTAG
  URL http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocTag.gz
  SOURCE_DIR ITKDoxygenTAG
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygenTAG_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG )

ExternalProject_Add( ITKDoxygen
  URL http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocHtml.tar.gz
  SOURCE_DIR ITKDoxygen
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygen_DIR ${CMAKE_BINARY_DIR}/ITKDoxygen )

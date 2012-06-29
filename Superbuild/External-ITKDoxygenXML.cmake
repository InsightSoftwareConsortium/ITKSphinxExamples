ExternalProject_Add( ITKDoxygenXML
  URL http://public.kitware.com/pub/itk/NightlyDoxygen/InsightDoxygenDocXml.tar.gz
  SOURCE_DIR ITKDoxygenXML
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygenXML_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenXML )

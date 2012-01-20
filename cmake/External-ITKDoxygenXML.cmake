include( ExternalProject )

ExternalProject_Add( ITKDoxygenXML
  URL http://dl.dropbox.com/u/15135983/itk-doxygen-xml.tar.bz2
  SOURCE_DIR ITKDoxygenXML
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygenXML_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenXML )

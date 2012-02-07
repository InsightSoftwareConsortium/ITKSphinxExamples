ExternalProject_Add( ITKDoxygenTAG
  URL http://dl.dropbox.com/u/15135983/InsightDoxygen.tag.tar.bz2
  SOURCE_DIR ITKDoxygenTAG
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygenTAG_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG )

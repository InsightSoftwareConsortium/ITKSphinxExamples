ExternalProject_Add( ITKDoxygen
  URL http://dl.dropbox.com/u/15135983/itk-doxygen.tar.bz2
  SOURCE_DIR ITKDoxygen
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set( ITKDoxygen_DIR ${CMAKE_BINARY_DIR}/ITKDoxygen )

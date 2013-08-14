#---------------------------------------------------------------------------
# Get and build itk

if( NOT ITK_TAG )
  # ITK master 2013-08-14
  set( ITK_TAG "80fd1523d2294044c0da7bea5919f8119c1a800e" )
endif()

ExternalProject_Add( ITK
  GIT_REPOSITORY "${git_protocol}://itk.org/ITK.git"
  GIT_TAG "${ITK_TAG}"
  SOURCE_DIR ITK
  BINARY_DIR ITK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DITK_BUILD_ALL_MODULES:BOOL=ON
#    -DVTK_DIR:PATH=${VTK_DIR}
#    -DModule_ITKVtkGlue:BOOL=ON
    -DITK_USE_REVIEW:BOOL=ON
  INSTALL_COMMAND ""
#  DEPENDS VTK
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

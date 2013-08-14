#---------------------------------------------------------------------------
# Get and build itk

if( NOT ITK_TAG )
  # ITK master 2013-07-09
  set( ITK_TAG "d73c465ed4b65d1c81e00b4e68ef4c859a1f7e10" )
endif()

set( _vtk_args )
set( _vtk_depends )
if( VTK_DIR OR ITKExamples_USE_VTK )
  set( _vtk_args "-DVTK_DIR:PATH=${VTK_DIR}"
    -DModule_ITKVtkGlue:BOOL=ON
    -DModule_ITKLevelSetsv4Visualization:BOOL=ON
    )
  set( _vtk_depends VTK )
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
    -DITK_USE_REVIEW:BOOL=ON
    ${_vtk_args}
  INSTALL_COMMAND ""
  DEPENDS ${_vtk_depends}
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

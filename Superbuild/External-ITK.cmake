#---------------------------------------------------------------------------
# Get and build itk

if( NOT ITK_TAG )
  # ITK master 2013-09-08
  set( ITK_TAG "130d80b376e61a30661d7e7fcbd98ed338dd48fb" )
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

set( _opencv_args )
set( _opencv_depends )
if( OpenCV_DIR OR ITKExamples_USE_OpenCV )
  set( _opencv_args "-DOpenCV_DIR:PATH=${OpenCV_DIR}"
    -DModule_ITKVideoBridgeOpenCV:BOOL=ON
    )
  set( _opencv_depends OpenCV )
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
    -DITK_BUILD_DEFAULT_MODULES:BOOL=ON
    -DModule_ITKReview:BOOL=ON
    ${_vtk_args}
    ${_opencv_args}
  INSTALL_COMMAND ""
  DEPENDS ${_vtk_depends} ${_opencv_depends}
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

#---------------------------------------------------------------------------
# Get and build itk

if( NOT ITK_TAG )
  set( ITK_TAG "v4.8.0" )
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

set(use_shared_libs OFF)
set( _wrap_python_args )
if( ITKExamples_USE_WRAP_PYTHON )
  set(use_shared_libs ON)
  set( _wrap_python_args -DITK_WRAP_PYTHON:BOOL=ON)
endif()

ExternalProject_Add( ITK
  GIT_REPOSITORY "${git_protocol}://itk.org/ITK.git"
  GIT_TAG "${ITK_TAG}"
  SOURCE_DIR ITK
  BINARY_DIR ITK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=${use_shared_libs}
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DITK_BUILD_DEFAULT_MODULES:BOOL=ON
    -DModule_ITKReview:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
    ${_vtk_args}
    ${_opencv_args}
    ${_wrap_python_args}
  INSTALL_COMMAND ""
  DEPENDS ${_vtk_depends} ${_opencv_depends}
  LOG_BUILD 0
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

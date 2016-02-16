#---------------------------------------------------------------------------
# Get and build itk

if( NOT ITK_TAG )
  # ITK master 2016-02-09
  set( ITK_TAG "9473a5128cbb1fdefd530ffa269e847385610abd" )
endif()

set( _vtk_args )
set( _vtk_depends )
if( VTK_DIR OR ITKExamples_USE_VTK )
  set( _vtk_args "-DVTK_DIR:PATH=${VTK_DIR}"
    -DModule_ITKVtkGlue:BOOL=ON
    -DModule_ITKLevelSetsv4Visualization:BOOL=ON
    )
  if( NOT VTK_DIR )
    set( _vtk_depends VTK )
  endif()
else()
  set( _vtk_args
    -DModule_ITKVtkGlue:BOOL=OFF
    -DModule_ITKLevelSetsv4Visualization:BOOL=OFF
    )
endif()

set( _opencv_args )
set( _opencv_depends )
if( OpenCV_DIR OR ITKExamples_USE_OpenCV )
  set( _opencv_args "-DOpenCV_DIR:PATH=${OpenCV_DIR}"
    -DModule_ITKVideoBridgeOpenCV:BOOL=ON
    )
  if( NOT OpenCV_DIR )
    set( _opencv_depends OpenCV )
  endif()
else()
  set( _opencv_args
    -DModule_ITKVideoBridgeOpenCV:BOOL=OFF
    )
endif()

set(_wrap_python_args )
if(ITKExamples_USE_WRAP_PYTHON)
  set(_python_depends)
  if(NOT EXISTS PYTHON_EXECUTABLE)
    set(_python_depends Python)
  endif()
  list(APPEND _wrap_python_args "-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/Python-install")
  list(APPEND _wrap_python_args -DITK_WRAP_PYTHON:BOOL=ON)
  list(APPEND _wrap_python_args
    "-DPYTHON_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE}"
    "-DPYTHON_INCLUDE_DIR:PATH=${PYTHON_INCLUDE_DIR}"
    "-DPYTHON_LIBRARY:PATH=${PYTHON_LIBRARY}"
    )
  if(UNIX)
    list(APPEND _wrap_python_args "-DPY_SITE_PACKAGES_PATH:PATH=${PY_SITE_PACKAGES_PATH}")
  endif()
  find_package(NumPy)
  if(NUMPY_FOUND)
    list(APPEND _wrap_python_args -DModule_BridgeNumPy:BOOL=ON)
  else()
    list(APPEND _wrap_python_args -DModule_BridgeNumPy:BOOL=OFF)
  endif()
  list(APPEND _wrap_python_args INSTALL_COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_BINARY_DIR}/ITK-build/Wrapping/Generators/Python/${CMAKE_CFG_INTDIR}/WrapITK.pth"
    "${PY_SITE_PACKAGES_PATH}"
    )
else()
  set(_wrap_python_args -DITK_WRAP_PYTHON:BOOL=OFF
    -DModule_BridgeNumPy:BOOL=OFF
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "ITK install skipped")
endif()

ExternalProject_Add(ITK
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
    -DITK_LEGACY_SILENT:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
    "-DITK_USE_SYSTEM_ZLIB:BOOL=ON"
    "-DZLIB_ROOT:PATH=${ZLIB_ROOT}"
    "-DZLIB_INCLUDE_DIR:PATH=${ZLIB_INCLUDE_DIR}"
    "-DZLIB_LIBRARY:FILEPATH=${ZLIB_LIBRARY}"
    ${_vtk_args}
    ${_opencv_args}
    ${_wrap_python_args}
  DEPENDS ${_vtk_depends} ${_opencv_depends} ${_python_depends} zlib
  LOG_BUILD 0
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

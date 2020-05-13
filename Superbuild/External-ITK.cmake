#---------------------------------------------------------------------------
# Get and build itk

if(NOT ITK_TAG)
  set(ITK_TAG "v5.1.0")
endif()

set(_vtk_args)
if(VTK_DIR OR ITKExamples_USE_VTK)
  set( _vtk_args "-DVTK_DIR:PATH=${VTK_DIR}"
    -DModule_ITKVtkGlue:BOOL=ON
    )
else()
  set(_vtk_args
    -DModule_ITKVtkGlue:BOOL=OFF
    )
endif()

set(_opencv_args )
if(OpenCV_DIR OR ITKExamples_USE_OpenCV)
  set( _opencv_args "-DOpenCV_DIR:PATH=${OpenCV_DIR}"
    -DModule_ITKVideoBridgeOpenCV:BOOL=ON
    )
else()
  set(_opencv_args
    -DModule_ITKVideoBridgeOpenCV:BOOL=OFF
    )
endif()

set(_wrap_python_args )
if(ITKExamples_USE_WRAP_PYTHON)
  set(_python_depends)
  if(NOT EXISTS Python3_EXECUTABLE)
    set(_python_depends ITKPython)
  endif()
  set(_wrap_python_args
    "-DPython3_EXECUTABLE:FILEPATH=${ITKPython3_EXECUTABLE}"
    )
endif()

set(_apple_args)
if(APPLE)
  set(_apple_args
    "-DBUILD_SHARED_LIBS:BOOL=ON"
    )
endif()
set(_windows_args)
set(_zlib_deps zlib)
if(WIN32)
  set(_windows_args
    "-DITK_USE_SYSTEM_ZLIB:BOOL=OFF"
    )
  set(_zlib_deps )
endif()

ExternalProject_Add(ITK
  GIT_REPOSITORY "${git_protocol}://github.com/InsightSoftwareConsortium/ITK.git"
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
    ${_apple_args}
    ${_windows_args}
  INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "ITK install skipped"
  DEPENDS ${ITK_DEPENDENCIES} ${_python_depends} ${_zlib_deps}
  LOG_BUILD 0
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

#---------------------------------------------------------------------------
# Get and build itk

if(NOT ITK_TAG)
  # ITK release 2024-05-22
  set(ITK_TAG "v5.4.0")
endif()

set(_vtk_args)
if(VTK_DIR OR ITKSphinxExamples_USE_VTK)
  set( _vtk_args "-DVTK_DIR:PATH=${VTK_DIR}"
    -DModule_ITKVtkGlue:BOOL=ON
    )
else()
  set(_vtk_args
    -DModule_ITKVtkGlue:BOOL=OFF
    )
endif()

set(_opencv_args )
if(OpenCV_DIR OR ITKSphinxExamples_USE_OpenCV)
  set( _opencv_args "-DOpenCV_DIR:PATH=${OpenCV_DIR}"
    -DModule_ITKVideoBridgeOpenCV:BOOL=ON
    )
else()
  set(_opencv_args
    -DModule_ITKVideoBridgeOpenCV:BOOL=OFF
    )
endif()

set(_wrap_python_args )
if(ITKSphinxExamples_USE_WRAP_PYTHON)
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
    -DITK_LEGACY_REMOVE:BOOL=ON
    -DITK_LEGACY_SILENT:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
    ${_vtk_args}
    ${_opencv_args}
    ${_wrap_python_args}
    ${_apple_args}
  INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "ITK install skipped"
  DEPENDS ${ITK_DEPENDENCIES} ${_python_depends}
  LOG_BUILD 0
)

set(ITK_DIR ${CMAKE_BINARY_DIR}/ITK-build)

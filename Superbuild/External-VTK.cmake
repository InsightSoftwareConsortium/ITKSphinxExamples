#---------------------------------------------------------------------------
# Get and build vtk

if(NOT VTK_TAG)
  set(VTK_TAG "v9.0.1")
endif()

set(PYTHON_EXECUTABLE "${ITKPYTHON_EXECUTABLE}")

ExternalProject_Add(VTK
  GIT_REPOSITORY "https://gitlab.kitware.com/VTK/VTK.git"
  GIT_TAG "${VTK_TAG}"
  SOURCE_DIR VTK
  BINARY_DIR VTK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    ${_wrap_python_args}
    -DBUILD_SHARED_LIBS:BOOL=ON
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DVTK_Group_Web:BOOL=ON
    -DModule_vtkImagingMath:BOOL=ON
    -DVTK_WRAP_PYTHON:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
    "-DPython3_EXECUTABLE:FILEPATH=${PYTHON_EXECUTABLE}"
    -DVTK_USE_SYSTEM_ZLIB:BOOL=ON
    "-DZLIB_ROOT:PATH=${ZLIB_ROOT}"
    "-DZLIB_INCLUDE_DIR:PATH=${ZLIB_INCLUDE_DIR}"
    "-DZLIB_LIBRARY:FILEPATH=${ZLIB_LIBRARY}"
  INSTALL_COMMAND ""
  LOG_DOWNLOAD 0
  LOG_UPDATE 0
  DEPENDS zlib
)

set(VTK_DIR ${CMAKE_BINARY_DIR}/VTK-build)

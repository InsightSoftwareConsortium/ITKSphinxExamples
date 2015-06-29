#---------------------------------------------------------------------------
# Get and build vtk

if( NOT VTK_TAG )
  set( VTK_TAG "v6.2.0" )
endif()

ExternalProject_Add(VTK
  GIT_REPOSITORY "${git_protocol}://vtk.org/VTK.git"
  GIT_TAG "${VTK_TAG}"
  SOURCE_DIR VTK
  BINARY_DIR VTK-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=TRUE
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DVTK_Group_Web:BOOL=ON
    -DVTK_WRAP_PYTHON:BOOL=ON
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
  INSTALL_COMMAND ""
  LOG_DOWNLOAD 0
  LOG_UPDATE 0
)

set(VTK_DIR ${CMAKE_BINARY_DIR}/VTK-build)

find_package(Git)

if(NOT GIT_FOUND)
  message(ERROR "Cannot find git. git is required for Superbuild")
endif()

option( USE_GIT_PROTOCOL "If behind a firewall turn this off to use http instead." ON)

set(git_protocol "git")
if(NOT USE_GIT_PROTOCOL)
  set(git_protocol "http")
endif()

include( ExternalProject )

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

set( ITKExamples_DEPENDENCIES )

if(NOT VTK_DIR)
  include( ${CMAKE_SOURCE_DIR}/External-VTK.cmake )
  list( APPEND ITKExamples_DEPENDENCIES VTK )
endif()

if(NOT ITK_DIR)
  include( ${CMAKE_SOURCE_DIR}/External-ITK.cmake )
  list( APPEND ITKExamples_DEPENDENCIES ITK )
endif()

ExternalProject_Add( ITK_EXAMPLES
  DEPENDS ${ITKExamples_DEPENDENCIES}
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
  BINARY_DIR ITKExamples-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_SHARED_LIBS:BOOL=FALSE
     # ITK
    -DITK_DIR:PATH=${ITK_DIR}
    # VTK
    # -DVTK_DIR:PATH=${VTK_DIR}
  INSTALL_COMMAND ""
)

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

#if(NOT VTK_DIR)
#  include( ${CMAKE_SOURCE_DIR}/External-VTK.cmake )
#  list( APPEND ITKExamples_DEPENDENCIES VTK )
#endif()

if(NOT ITK_DIR)
  include( ${CMAKE_SOURCE_DIR}/External-ITK.cmake )
  list( APPEND ITKExamples_DEPENDENCIES ITK )
endif()

option( BUILD_DOCUMENTATION "Build documentation" OFF )

if( ${BUILD_DOCUMENTATION} )

  option( DOC_WITH_LOCAL_DOXYGEN "Download ITK Doxygen documentation" OFF )

  if( ${DOC_WITH_LOCAL_DOXYGEN} )
    if(NOT ITKDoxygen_DIR )
      include( ${CMAKE_SOURCE_DIR}/External-ITKDoxygen.cmake )
      list( APPEND ITKExamples_DEPENDENCIES ITKDoxygen )
    endif()
  endif()

  if(NOT ITKDoxygenXML_DIR )
    include( ${CMAKE_SOURCE_DIR}/External-ITKDoxygenXML.cmake )
    list( APPEND ITKExamples_DEPENDENCIES ITKDoxygenXML )
  endif()

  if(NOT ITKDoxygenTAG_DIR )
    include( ${CMAKE_SOURCE_DIR}/External-ITKDoxygenTAG.cmake )
    list( APPEND ITKExamples_DEPENDENCIES ITKDoxygenTAG )
  endif()
endif()

option( BUILD_TESTING "Build testing" OFF )

ExternalProject_Add( ITKExamples
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
    -DITKDoxygen_DIR:PATH=${ITKDoxygen_DIR}
    -DITKDoxygenXML_DIR:PATH=${ITKDoxygenXML_DIR}
    -DITKDoxygenTAG_DIR:PATH=${ITKDoxygenTAG_DIR}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING}
    -DBUILD_DOCUMENTATION:BOOL=${BUILD_DOCUMENTATION}
    -DDOC_WITH_LOCAL_DOXYGEN:BOOL=${DOC_WITH_LOCAL_DOXYGEN}
  INSTALL_COMMAND ""
)

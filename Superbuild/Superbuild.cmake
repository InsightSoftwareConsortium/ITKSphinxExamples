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

set(ep_common_args
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  )

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

set( ITKExamples_DEPENDENCIES )

option( ITKExamples_USE_VTK "Add VTK to the superbuild." OFF )

if( NOT VTK_DIR AND ITKExamples_USE_VTK )
  include( ${CMAKE_SOURCE_DIR}/External-VTK.cmake )
  list( APPEND ITKExamples_DEPENDENCIES VTK )
endif()

option( ITKExamples_USE_OpenCV "Add OpenCV to the superbuild" OFF )
if( NOT OpenCV_DIR AND ITKExamples_USE_OpenCV )
  include( ${CMAKE_SOURCE_DIR}/External-OpenCV.cmake )
  list( APPEND ITKExamples_DEPENDENCIES OpenCV )
endif()

if( NOT ITK_DIR )
  include( ${CMAKE_SOURCE_DIR}/External-ITK.cmake )
  list( APPEND ITKExamples_DEPENDENCIES ITK )
endif()

option( BUILD_DOCUMENTATION "Build documentation" OFF )
set( _build_doc_args )
if( BUILD_DOCUMENTATION )
  if( ITKDoxygen_DIR )
    set( _build_doc_args "${_build_doc_args} -DITKDoxygen_DIR:PATH=${ITKDoxygen_DIR}" )
  endif()
  if( ITKDoxygenXML_DIR )
    set( _build_doc_args "${_build_doc_args} -DITKDoxygenXML_DIR:PATH=${ITKDoxygenXML_DIR}" )
  endif()
  if( ITKDoxygenTAG_DIR )
    set( _build_doc_args "${_build_doc_args} -DITKDoxygenTAG_DIR:PATH=${ITKDoxygenTAG_DIR}" )
  endif()
  if( DOC_WITH_LOCAL_DOXYGEN )
    set( _build_doc_args "${_build_doc_args} -DDOC_WITH_LOCAL_DOXYGEN:PATH=${DOC_WITH_LOCAL_DOXYGEN}" )
  endif()
endif()

include( CTest )
option( BUILD_TESTING "Build testing" OFF )

ExternalProject_Add( ITKExamples
  DEPENDS ${ITKExamples_DEPENDENCIES}
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
  BINARY_DIR ITKExamples-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    ${_build_doc_args}
    -DBUILD_SHARED_LIBS:BOOL=FALSE
     # ITK
    -DITK_DIR:PATH=${ITK_DIR}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING}
    -DBUILD_DOCUMENTATION:BOOL=${BUILD_DOCUMENTATION}
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
  INSTALL_COMMAND ""
)

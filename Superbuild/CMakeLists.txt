cmake_minimum_required( VERSION 2.8.6 )

if( COMMAND CMAKE_POLICY )
  cmake_policy( SET CMP0003 NEW )
endif( COMMAND CMAKE_POLICY )

project( ITKExamples )

if( CMAKE_HOST_WIN32 )
  string( LENGTH "${ITKExamples_SOURCE_DIR}" source_len )
  if( ${source_len} GREATER 15 )
    message( FATAL_ERROR
    "The build directory is currently too long, ${source_len} characters. "
    "Please move the Examples build directory to a shorter path."
    )
  endif()
  string( LENGTH "${ITKExamples_BINARY_DIR}" binary_len )
  if( ${binary_len} GREATER 15 )
    message( FATAL_ERROR
    "The build directory is currently too long, ${binary_len} characters. "
    "Please set the Examples build directory to a shorter path."
    )
  endif()
endif()

include( ${CMAKE_SOURCE_DIR}/Superbuild.cmake )

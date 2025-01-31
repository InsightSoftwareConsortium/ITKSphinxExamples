cmake_minimum_required(VERSION 3.16.3)

project(ITKSphinxExamples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../CMake")

if(CMAKE_HOST_WIN32)
  string(LENGTH "${ITKSphinxExamples_SOURCE_DIR}" source_len)
  if(${source_len} GREATER 30)
    message(FATAL_ERROR
    "The source directory is currently too long, ${source_len} characters. "
    "Please move the Examples build directory to a shorter path."
    )
  endif()
  string(LENGTH "${ITKSphinxExamples_BINARY_DIR}" binary_len)
  if(${binary_len} GREATER 30)
    message(FATAL_ERROR
    "The build directory is currently too long, ${binary_len} characters. "
    "Please set the Examples build directory to a shorter path."
    )
  endif()
endif()

include(${CMAKE_SOURCE_DIR}/Superbuild.cmake)

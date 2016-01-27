if(itk-module)
  set(ITK_DIR ${ITK_BINARY_DIR})
  if(NOT EXISTS "${ITK_DIR}/ITKConfig.cmake")
    return()
  endif()
endif()
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# To avoid linker issues.
if(ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

if(${ITK_VERSION_MAJOR} LESS 4)
  message(SEND_ERROR "ITKExamples require at least ITK 4.0.0")
endif()

if(BUILD_DOCUMENTATION)
  find_package(PythonInterp REQUIRED)

  # Set here the proper version of Python required to be able to build
  # tarballs for each example
  set(PYTHON_REQUIRED_VERSION 2.7)
  if(${PYTHON_VERSION_STRING} LESS ${PYTHON_REQUIRED_VERSION})
    message(SEND_ERROR "Building the documentation requires Python >= ${PYTHON_REQUIRED_VERSION}")
  endif()
endif()

if(WIN32)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
endif()

# For comparing example outputs to their regression baseline's.
add_executable(ImageCompareCommand ImageCompareCommand.cxx)
target_link_libraries(ImageCompareCommand ${ITK_LIBRARIES})

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMake/ITKExamplesMacros.cmake)

add_subdirectory(Bridge)
add_subdirectory(Core)
add_subdirectory(Compatibility)
add_subdirectory(External)
add_subdirectory(Filtering)
add_subdirectory(GPU)
add_subdirectory(IO)
add_subdirectory(Numerics)
add_subdirectory(Nonunit)
add_subdirectory(Registration)
add_subdirectory(Segmentation)
add_subdirectory(Video)

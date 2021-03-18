if(itk-module)
  set(ITK_DIR ${ITK_BINARY_DIR})
  if(NOT EXISTS "${ITK_DIR}/ITKConfig.cmake")
    return()
  endif()
endif()
find_package(ITK 5.2.0 REQUIRED)
include(${ITK_USE_FILE})

# To avoid linker issues.
# Module_ITKVtkGlue is true when building inside ITK
# ITKVtkGlue_LOADED is true when SuperBuild ITKEx stand-alone
set(ENABLE_QUICKVIEW OFF)

if(Module_ITKVtkGlue OR ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include_directories(${VTK_INCLUDE_DIRS})
  set(ENABLE_QUICKVIEW ON)
  add_definitions(-DENABLE_QUICKVIEW)
endif()

if(BUILD_DOCUMENTATION)
  if(NOT PYTHON_EXECUTABLE)
    find_package(PythonInterp 3.6 REQUIRED)
    if(NOT PYTHONINTERP_FOUND)
      message(SEND_ERROR "Building the documentation requires Python")
    else()
      # Set here the proper version of Python required to be able to build
      # tarballs for each example
      set(PYTHON_REQUIRED_VERSION 3.6)
      if("${PYTHON_VERSION_STRING}" VERSION_LESS ${PYTHON_REQUIRED_VERSION})
        message(SEND_ERROR "Building the documentation requires Python >= ${PYTHON_REQUIRED_VERSION}: ${PYTHON_VERSION_STRING} found at ${PYTHON_EXECUTABLE}")
      endif()
    endif()
  endif()
endif()

if(WIN32)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
endif()

# For comparing example outputs to their regression baseline's.
add_executable(ImageCompareCommand ImageCompareCommand.cxx)
target_link_libraries(ImageCompareCommand ${ITK_LIBRARIES})

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMake/ITKExamplesMacros.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Developer)

add_subdirectory(Bridge)
add_subdirectory(Core)
add_subdirectory(External)
add_subdirectory(Filtering)
add_subdirectory(GPU)
add_subdirectory(IO)
add_subdirectory(Numerics)
add_subdirectory(Nonunit)
add_subdirectory(Registration)
add_subdirectory(Segmentation)
add_subdirectory(Video)

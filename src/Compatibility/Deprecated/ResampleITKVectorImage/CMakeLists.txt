cmake_minimum_required(VERSION 3.10.2)

project(ResampleITKVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ResampleITKVectorImage Code.cxx)
target_link_libraries(ResampleITKVectorImage ${ITK_LIBRARIES})

install(TARGETS ResampleITKVectorImage
  DESTINATION bin/ITKExamples/Compatibility/Deprecated
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Compatibility/Deprecated/ResampleITKVectorImage/
  COMPONENT Code
  )

enable_testing()
add_test(NAME ResampleITKVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleITKVectorImage)

cmake_minimum_required(VERSION 3.10.2)

project(ResampleSegmentedImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ResampleSegmentedImage Code.cxx)
target_link_libraries(ResampleSegmentedImage ${ITK_LIBRARIES})

install(TARGETS ResampleSegmentedImage
  DESTINATION bin/ITKExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/ImageFunction/ResampleSegmentedImage/
  COMPONENT Code
  )

enable_testing()
add_test(NAME ResampleSegmentedImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleSegmentedImage)

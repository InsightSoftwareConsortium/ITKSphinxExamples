cmake_minimum_required(VERSION 3.10.2)

project(ResampleRGBImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ResampleRGBImage Code.cxx)
target_link_libraries(ResampleRGBImage ${ITK_LIBRARIES})

install(TARGETS ResampleRGBImage
  DESTINATION bin/ITKExamples/Compatibility/Deprecated
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Compatibility/Deprecated/ResampleRGBImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ResampleRGBImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleRGBImage)

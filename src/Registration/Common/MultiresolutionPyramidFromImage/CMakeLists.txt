cmake_minimum_required(VERSION 3.10.2)

project(MultiresolutionPyramidFromImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MultiresolutionPyramidFromImage Code.cxx)
target_link_libraries(MultiresolutionPyramidFromImage ${ITK_LIBRARIES})

install(TARGETS MultiresolutionPyramidFromImage
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/MultiresolutionPyramidFromImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultiresolutionPyramidFromImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiresolutionPyramidFromImage)


cmake_minimum_required(VERSION 3.10.2)

project(SmoothRGBImageUsingMinMaxCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothRGBImageUsingMinMaxCurvatureFlow Code.cxx)
target_link_libraries(SmoothRGBImageUsingMinMaxCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS SmoothRGBImageUsingMinMaxCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/CurvatureFlow
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/CurvatureFlow/SmoothRGBImageUsingMinMaxCurvatureFlow/
  COMPONENT Code
  )


enable_testing()

add_test(NAME SmoothRGBImageUsingMinMaxCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothRGBImageUsingMinMaxCurvatureFlow)

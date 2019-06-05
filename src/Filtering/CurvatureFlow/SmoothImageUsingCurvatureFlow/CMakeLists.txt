cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageUsingCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothImageUsingCurvatureFlow Code.cxx)
target_link_libraries(SmoothImageUsingCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS SmoothImageUsingCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/CurvatureFlow
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/CurvatureFlow/SmoothImageUsingCurvatureFlow/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageUsingCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageUsingCurvatureFlow)


cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageUsingMinMaxCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothImageUsingMinMaxCurvatureFlow Code.cxx)
target_link_libraries(SmoothImageUsingMinMaxCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS SmoothImageUsingMinMaxCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/CurvatureFlow
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/CurvatureFlow/SmoothImageUsingMinMaxCurvatureFlow/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageUsingMinMaxCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageUsingMinMaxCurvatureFlow
        Gourds.png
        5)

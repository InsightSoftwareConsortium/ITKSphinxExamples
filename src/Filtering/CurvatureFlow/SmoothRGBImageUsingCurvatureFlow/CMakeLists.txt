cmake_minimum_required(VERSION 3.10.2)

project(SmoothRGBImageUsingCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothRGBImageUsingCurvatureFlow Code.cxx)
target_link_libraries(SmoothRGBImageUsingCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS SmoothRGBImageUsingCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/CurvatureFlow
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/CurvatureFlow/SmoothRGBImageUsingCurvatureFlow/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothRGBImageUsingCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothRGBImageUsingCurvatureFlow
    Gourds.png
    200)

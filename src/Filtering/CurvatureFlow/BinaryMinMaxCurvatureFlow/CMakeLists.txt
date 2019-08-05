cmake_minimum_required(VERSION 3.10.2)

project(BinaryMinMaxCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BinaryMinMaxCurvatureFlow Code.cxx)
target_link_libraries(BinaryMinMaxCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS BinaryMinMaxCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/CurvatureFlow
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/CurvatureFlow/BinaryMinMaxCurvatureFlow/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BinaryMinMaxCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BinaryMinMaxCurvatureFlow
    Yinyang.png
    10)

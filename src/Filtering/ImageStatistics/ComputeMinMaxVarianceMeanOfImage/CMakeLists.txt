cmake_minimum_required(VERSION 3.10.2)

project(ComputeMinMaxVarianceMeanOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeMinMaxVarianceMeanOfImage Code.cxx)
target_link_libraries(ComputeMinMaxVarianceMeanOfImage ${ITK_LIBRARIES})

install(TARGETS ComputeMinMaxVarianceMeanOfImage
  DESTINATION bin/ITKExamples/Filtering/ImageStatistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageStatistics/ComputeMinMaxVarianceMeanOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeMinMaxVarianceMeanOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeMinMaxVarianceMeanOfImage)

cmake_minimum_required(VERSION 3.10.2)

project(ComputeLocalNoise)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeLocalNoise Code.cxx)
target_link_libraries(ComputeLocalNoise ${ITK_LIBRARIES})

install(TARGETS ComputeLocalNoise
  DESTINATION bin/ITKExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFilterBase/ComputeLocalNoise/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeLocalNoiseTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeLocalNoise)


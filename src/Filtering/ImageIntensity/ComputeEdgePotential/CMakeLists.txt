cmake_minimum_required(VERSION 3.10.2)

project(ComputeEdgePotential)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeEdgePotential Code.cxx)
target_link_libraries(ComputeEdgePotential ${ITK_LIBRARIES})

install(TARGETS ComputeEdgePotential
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ComputeEdgePotential/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeEdgePotentialTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeEdgePotential)

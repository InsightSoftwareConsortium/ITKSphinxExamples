cmake_minimum_required(VERSION 3.16.3)

project(DistributeSamplingUsingGMM)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DistributeSamplingUsingGMM Code.cxx)
target_link_libraries(DistributeSamplingUsingGMM ${ITK_LIBRARIES})

install(TARGETS DistributeSamplingUsingGMM
  DESTINATION bin/ITKSphinxExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Statistics/DistributeSamplingUsingGMM/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DistributeSamplingUsingGMMTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DistributeSamplingUsingGMM)


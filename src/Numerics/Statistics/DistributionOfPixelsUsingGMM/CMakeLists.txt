cmake_minimum_required(VERSION 3.10.2)

project(DistributionOfPixelsUsingGMM)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DistributionOfPixelsUsingGMM Code.cxx)
target_link_libraries(DistributionOfPixelsUsingGMM ${ITK_LIBRARIES})

install(TARGETS DistributionOfPixelsUsingGMM
  DESTINATION bin/ITKSphinxExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Statistics/DistributionOfPixelsUsingGMM/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DistributionOfPixelsUsingGMMTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DistributionOfPixelsUsingGMM)

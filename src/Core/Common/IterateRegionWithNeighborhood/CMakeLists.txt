cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithNeighborhood)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateRegionWithNeighborhood Code.cxx)
target_link_libraries(IterateRegionWithNeighborhood ${ITK_LIBRARIES})

install(TARGETS IterateRegionWithNeighborhood
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithNeighborhood/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithNeighborhoodTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithNeighborhood)


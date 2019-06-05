cmake_minimum_required(VERSION 3.10.2)

project(AssignContiguousLabelsToConnectedRegions)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AssignContiguousLabelsToConnectedRegions Code.cxx)
target_link_libraries(AssignContiguousLabelsToConnectedRegions ${ITK_LIBRARIES})

install(TARGETS AssignContiguousLabelsToConnectedRegions
  DESTINATION bin/ITKExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/ConnectedComponents/AssignContiguousLabelsToConnectedRegions/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AssignContiguousLabelsToConnectedRegionsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AssignContiguousLabelsToConnectedRegions)

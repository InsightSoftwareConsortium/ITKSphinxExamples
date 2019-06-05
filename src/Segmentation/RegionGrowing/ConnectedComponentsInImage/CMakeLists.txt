cmake_minimum_required(VERSION 3.10.2)

project(ConnectedComponentsInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConnectedComponentsInImage Code.cxx)
target_link_libraries(ConnectedComponentsInImage ${ITK_LIBRARIES})

install(TARGETS ConnectedComponentsInImage
  DESTINATION bin/ITKExamples/Segmentation/RegionGrowing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/RegionGrowing/ConnectedComponentsInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConnectedComponentsInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConnectedComponentsInImage)


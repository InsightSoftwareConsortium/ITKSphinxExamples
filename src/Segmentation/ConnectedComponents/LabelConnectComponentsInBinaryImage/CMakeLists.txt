cmake_minimum_required(VERSION 3.10.2)

project(LabelConnectComponentsInBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LabelConnectComponentsInBinaryImage Code.cxx)
target_link_libraries(LabelConnectComponentsInBinaryImage ${ITK_LIBRARIES})

install(TARGETS LabelConnectComponentsInBinaryImage
  DESTINATION bin/ITKSphinxExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Segmentation/ConnectedComponents/LabelConnectComponentsInBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelConnectComponentsInBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelConnectComponentsInBinaryImage)

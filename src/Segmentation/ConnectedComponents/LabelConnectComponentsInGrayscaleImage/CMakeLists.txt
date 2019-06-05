cmake_minimum_required(VERSION 3.10.2)

project(LabelConnectComponentsInGrayscaleImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LabelConnectComponentsInGrayscaleImage Code.cxx)
target_link_libraries(LabelConnectComponentsInGrayscaleImage ${ITK_LIBRARIES})

install(TARGETS LabelConnectComponentsInGrayscaleImage
  DESTINATION bin/ITKExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/ConnectedComponents/LabelConnectComponentsInGrayscaleImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelConnectComponentsInGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelConnectComponentsInGrayscaleImage)

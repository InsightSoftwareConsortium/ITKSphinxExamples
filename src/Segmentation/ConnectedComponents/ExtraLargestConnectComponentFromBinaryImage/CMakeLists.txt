cmake_minimum_required(VERSION 3.10.2)

project(ExtraLargestConnectComponentFromBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExtraLargestConnectComponentFromBinaryImage Code.cxx)
target_link_libraries(ExtraLargestConnectComponentFromBinaryImage ${ITK_LIBRARIES})

install(TARGETS ExtraLargestConnectComponentFromBinaryImage
  DESTINATION bin/ITKExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/ConnectedComponents/ExtraLargestConnectComponentFromBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtraLargestConnectComponentFromBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtraLargestConnectComponentFromBinaryImage
    Yinyang.png)

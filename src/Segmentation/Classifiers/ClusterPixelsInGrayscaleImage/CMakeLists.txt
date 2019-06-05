cmake_minimum_required(VERSION 3.10.2)

project(ClusterPixelsInGrayscaleImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ClusterPixelsInGrayscaleImage Code.cxx)
target_link_libraries(ClusterPixelsInGrayscaleImage ${ITK_LIBRARIES})

install(TARGETS ClusterPixelsInGrayscaleImage
  DESTINATION bin/ITKExamples/Segmentation/Classifiers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/Classifiers/ClusterPixelsInGrayscaleImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ClusterPixelsInGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ClusterPixelsInGrayscaleImage)

cmake_minimum_required(VERSION 3.10.2)

project(KMeansClusterOfPixelsInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(KMeansClusterOfPixelsInImage Code.cxx)
target_link_libraries(KMeansClusterOfPixelsInImage ${ITK_LIBRARIES})

install(TARGETS KMeansClusterOfPixelsInImage
  DESTINATION bin/ITKExamples/Segmentation/Classifiers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/Classifiers/KMeansClusterOfPixelsInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME KMeansClusterOfPixelsInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/KMeansClusterOfPixelsInImage)

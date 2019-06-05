cmake_minimum_required(VERSION 3.10.2)

project(KMeansClustering)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(KMeansClustering Code.cxx)
target_link_libraries(KMeansClustering ${ITK_LIBRARIES})

install(TARGETS KMeansClustering
  DESTINATION bin/ITKExamples/Segmentation/Classifiers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/Classifiers/KMeansClustering/
  COMPONENT Code
  )


enable_testing()
add_test(NAME KMeansClusteringTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/KMeansClustering)


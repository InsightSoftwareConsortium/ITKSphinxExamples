cmake_minimum_required(VERSION 3.10.2)

project(FindZeroCrossings)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FindZeroCrossings Code.cxx)
target_link_libraries(FindZeroCrossings ${ITK_LIBRARIES})

install(TARGETS FindZeroCrossings
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/FindZeroCrossings/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FindZeroCrossingsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FindZeroCrossings)

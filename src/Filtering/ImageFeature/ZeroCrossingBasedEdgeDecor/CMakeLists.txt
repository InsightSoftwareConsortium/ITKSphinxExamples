cmake_minimum_required(VERSION 3.10.2)

project(ZeroCrossingBasedEdgeDecor)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ZeroCrossingBasedEdgeDecor Code.cxx)
target_link_libraries(ZeroCrossingBasedEdgeDecor ${ITK_LIBRARIES})

install(TARGETS ZeroCrossingBasedEdgeDecor
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/ZeroCrossingBasedEdgeDecor/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ZeroCrossingBasedEdgeDecorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ZeroCrossingBasedEdgeDecor)


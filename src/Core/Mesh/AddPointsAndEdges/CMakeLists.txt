cmake_minimum_required(VERSION 3.10.2)

project(AddPointsAndEdges)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AddPointsAndEdges Code.cxx)
target_link_libraries(AddPointsAndEdges ${ITK_LIBRARIES})

install(TARGETS AddPointsAndEdges
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/AddPointsAndEdges/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AddPointsAndEdgesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddPointsAndEdges)

cmake_minimum_required(VERSION 3.10.2)

project(ApproxDistanceMapOfBinary)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ApproxDistanceMapOfBinary Code.cxx)
target_link_libraries(ApproxDistanceMapOfBinary ${ITK_LIBRARIES})

install(TARGETS ApproxDistanceMapOfBinary
  DESTINATION bin/ITKExamples/Filtering/DistanceMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/DistanceMap/ApproxDistanceMapOfBinary/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ApproxDistanceMapOfBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApproxDistanceMapOfBinary)

cmake_minimum_required(VERSION 3.10.2)

project(MaurerDistanceMapOfBinary)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MaurerDistanceMapOfBinary Code.cxx)
target_link_libraries(MaurerDistanceMapOfBinary ${ITK_LIBRARIES})

install(TARGETS MaurerDistanceMapOfBinary
  DESTINATION bin/ITKExamples/Filtering/DistanceMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/DistanceMap/MaurerDistanceMapOfBinary/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MaurerDistanceMapOfBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MaurerDistanceMapOfBinary)


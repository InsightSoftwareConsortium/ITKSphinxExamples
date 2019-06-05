cmake_minimum_required(VERSION 3.10.2)

project(SignedDistanceMapOfBinary)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SignedDistanceMapOfBinary Code.cxx)
target_link_libraries(SignedDistanceMapOfBinary ${ITK_LIBRARIES})

install(TARGETS SignedDistanceMapOfBinary
  DESTINATION bin/ITKExamples/Filtering/DistanceMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/DistanceMap/SignedDistanceMapOfBinary/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SignedDistanceMapOfBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SignedDistanceMapOfBinary)


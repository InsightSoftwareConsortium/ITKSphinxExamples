cmake_minimum_required(VERSION 3.10.2)

project(GeometricPropertiesOfRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GeometricPropertiesOfRegion Code.cxx)
target_link_libraries(GeometricPropertiesOfRegion ${ITK_LIBRARIES})

install(TARGETS GeometricPropertiesOfRegion
  DESTINATION bin/ITKExamples/Nonunit/Review
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Nonunit/Review/GeometricPropertiesOfRegion/
  COMPONENT Code
  )


enable_testing()


add_test(NAME GeometricPropertiesOfRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GeometricPropertiesOfRegion)


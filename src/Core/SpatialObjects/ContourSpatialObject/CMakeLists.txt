cmake_minimum_required(VERSION 3.10.2)

project(ContourSpatialObject)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ContourSpatialObject Code.cxx)
target_link_libraries(ContourSpatialObject ${ITK_LIBRARIES})

install(TARGETS ContourSpatialObject
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/ContourSpatialObject/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ContourSpatialObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ContourSpatialObject)

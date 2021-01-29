cmake_minimum_required(VERSION 3.10.2)

project(LineSpatialObject)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LineSpatialObject Code.cxx)
target_link_libraries(LineSpatialObject ${ITK_LIBRARIES})

install(TARGETS LineSpatialObject
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/LineSpatialObject/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LineSpatialObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LineSpatialObject)


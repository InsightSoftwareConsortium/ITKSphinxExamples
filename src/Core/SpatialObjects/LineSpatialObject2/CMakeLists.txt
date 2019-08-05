cmake_minimum_required(VERSION 3.10.2)

project(LineSpatialObject2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LineSpatialObject2 Code.cxx)
target_link_libraries(LineSpatialObject2 ${ITK_LIBRARIES})

install(TARGETS LineSpatialObject2
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/LineSpatialObject2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LineSpatialObject2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LineSpatialObject2)


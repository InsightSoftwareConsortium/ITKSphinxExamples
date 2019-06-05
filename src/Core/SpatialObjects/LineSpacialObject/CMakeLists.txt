cmake_minimum_required(VERSION 3.10.2)

project(LineSpacialObject)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LineSpacialObject Code.cxx)
target_link_libraries(LineSpacialObject ${ITK_LIBRARIES})

install(TARGETS LineSpacialObject
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/LineSpacialObject/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LineSpacialObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LineSpacialObject)


cmake_minimum_required(VERSION 3.16.3)

project(CreateALineSpatialObject)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateALineSpatialObject Code.cxx)
target_link_libraries(CreateALineSpatialObject ${ITK_LIBRARIES})

install(TARGETS CreateALineSpatialObject
  DESTINATION bin/ITKSphinxExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/SpatialObjects/CreateALineSpatialObject/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateALineSpatialObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateALineSpatialObject)


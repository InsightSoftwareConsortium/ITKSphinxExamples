cmake_minimum_required(VERSION 3.10.2)

project(ReadTransformFromFile)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ReadTransformFromFile Code.cxx)
target_link_libraries(ReadTransformFromFile ${ITK_LIBRARIES})

install(TARGETS ReadTransformFromFile
  DESTINATION bin/ITKExamples/IO/TransformBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/TransformBase/ReadTransformFromFile/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ReadTransformFromFileTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadTransformFromFile)

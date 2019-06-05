cmake_minimum_required(VERSION 3.10.2)

project(RegisterTransformWithTransformFactory)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegisterTransformWithTransformFactory Code.cxx)
target_link_libraries(RegisterTransformWithTransformFactory ${ITK_LIBRARIES})

install(TARGETS RegisterTransformWithTransformFactory
  DESTINATION bin/ITKExamples/IO/TransformFactory
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/IO/TransformFactory/RegisterTransformWithTransformFactory/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RegisterTransformWithTransformFactoryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegisterTransformWithTransformFactory)

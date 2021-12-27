cmake_minimum_required(VERSION 3.16.3)

project(MatrixInverse)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MatrixInverse Code.cxx)
target_link_libraries(MatrixInverse ${ITK_LIBRARIES})

install(TARGETS MatrixInverse
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/MatrixInverse/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MatrixInverseTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MatrixInverse
  )

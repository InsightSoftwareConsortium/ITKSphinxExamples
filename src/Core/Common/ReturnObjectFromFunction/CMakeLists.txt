cmake_minimum_required(VERSION 3.10.2)

project(ReturnObjectFromFunction)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ReturnObjectFromFunction Code.cxx)
target_link_libraries(ReturnObjectFromFunction ${ITK_LIBRARIES})

install(TARGETS ReturnObjectFromFunction
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/ReturnObjectFromFunction/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ReturnObjectFromFunctionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReturnObjectFromFunction)


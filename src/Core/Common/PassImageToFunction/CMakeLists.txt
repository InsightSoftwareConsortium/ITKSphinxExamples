cmake_minimum_required(VERSION 3.10.2)

project(PassImageToFunction)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PassImageToFunction Code.cxx)
target_link_libraries(PassImageToFunction ${ITK_LIBRARIES})

install(TARGETS PassImageToFunction
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/PassImageToFunction/
  COMPONENT Code
  )


enable_testing()
add_test(NAME PassImageToFunctionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PassImageToFunction)

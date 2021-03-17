cmake_minimum_required(VERSION 3.10.2)

project(RegionalMaximal)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegionalMaximal Code.cxx)
target_link_libraries(RegionalMaximal ${ITK_LIBRARIES})

install(TARGETS RegionalMaximal
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/RegionalMaximal/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RegionalMaximalTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegionalMaximal)


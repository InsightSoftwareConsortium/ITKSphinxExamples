cmake_minimum_required(VERSION 3.16.3)

project(GenerateStructureElementsWithAccurateArea)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GenerateStructureElementsWithAccurateArea Code.cxx)
target_link_libraries(GenerateStructureElementsWithAccurateArea ${ITK_LIBRARIES})

install(TARGETS GenerateStructureElementsWithAccurateArea
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/GenerateStructureElementsWithAccurateArea/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GenerateStructureElementsWithAccurateAreaTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GenerateStructureElementsWithAccurateArea)

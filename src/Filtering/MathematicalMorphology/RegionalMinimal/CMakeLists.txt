cmake_minimum_required(VERSION 3.10.2)

project(RegionalMinimal)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegionalMinimal Code.cxx)
target_link_libraries(RegionalMinimal ${ITK_LIBRARIES})

install(TARGETS RegionalMinimal
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/RegionalMinimal/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RegionalMinimalTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegionalMinimal)


cmake_minimum_required(VERSION 3.16.3)

project(DemonstrateAllOperators)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DemonstrateAllOperators Code.cxx)
target_link_libraries(DemonstrateAllOperators ${ITK_LIBRARIES})

install(TARGETS DemonstrateAllOperators
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/DemonstrateAllOperators/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DemonstrateAllOperatorsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DemonstrateAllOperators)

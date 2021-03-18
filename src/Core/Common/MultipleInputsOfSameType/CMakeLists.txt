cmake_minimum_required(VERSION 3.10.2)

project(MultipleInputsOfSameType)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MultipleInputsOfSameType Code.cxx)
target_link_libraries(MultipleInputsOfSameType ${ITK_LIBRARIES})

install(TARGETS MultipleInputsOfSameType
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/MultipleInputsOfSameType/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultipleInputsOfSameTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultipleInputsOfSameType)

cmake_minimum_required(VERSION 3.10.2)

project(MultipleOutputsOfDifferentType)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MultipleOutputsOfDifferentType Code.cxx)
target_link_libraries(MultipleOutputsOfDifferentType ${ITK_LIBRARIES})

install(TARGETS MultipleOutputsOfDifferentType
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MultipleOutputsOfDifferentType/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultipleOutputsOfDifferentTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultipleOutputsOfDifferentType)


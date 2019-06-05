cmake_minimum_required(VERSION 3.10.2)

project(VariableLengthVector)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(VariableLengthVector Code.cxx)
target_link_libraries(VariableLengthVector ${ITK_LIBRARIES})

install(TARGETS VariableLengthVector
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/VariableLengthVector/
  COMPONENT Code
  )


enable_testing()
add_test(NAME VariableLengthVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VariableLengthVector
  )

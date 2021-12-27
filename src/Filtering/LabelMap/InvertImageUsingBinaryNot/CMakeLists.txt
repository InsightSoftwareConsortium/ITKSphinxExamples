cmake_minimum_required(VERSION 3.16.3)

project(InvertImageUsingBinaryNot)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(InvertImageUsingBinaryNot Code.cxx)
target_link_libraries(InvertImageUsingBinaryNot ${ITK_LIBRARIES})

install(TARGETS InvertImageUsingBinaryNot
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/InvertImageUsingBinaryNot/
  COMPONENT Code
  )


enable_testing()
add_test(NAME InvertImageUsingBinaryNotTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/InvertImageUsingBinaryNot)


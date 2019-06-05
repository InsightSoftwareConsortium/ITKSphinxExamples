cmake_minimum_required(VERSION 3.10.2)

project(ClosingBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ClosingBinaryImage Code.cxx)
target_link_libraries(ClosingBinaryImage ${ITK_LIBRARIES})

install(TARGETS ClosingBinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/ClosingBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ClosingBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ClosingBinaryImage)


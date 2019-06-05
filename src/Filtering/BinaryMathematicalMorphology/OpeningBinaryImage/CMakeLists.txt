cmake_minimum_required(VERSION 3.10.2)

project(OpeningBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(OpeningBinaryImage Code.cxx)
target_link_libraries(OpeningBinaryImage ${ITK_LIBRARIES})

install(TARGETS OpeningBinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/OpeningBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME OpeningBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OpeningBinaryImage)

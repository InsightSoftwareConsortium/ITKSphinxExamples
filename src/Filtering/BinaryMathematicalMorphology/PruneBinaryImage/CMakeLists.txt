cmake_minimum_required(VERSION 3.10.2)

project(PruneBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PruneBinaryImage Code.cxx)
target_link_libraries(PruneBinaryImage ${ITK_LIBRARIES})

install(TARGETS PruneBinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/PruneBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME PruneBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PruneBinaryImage)

cmake_minimum_required(VERSION 3.10.2)

project(ThinImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ThinImage Code.cxx)
target_link_libraries(ThinImage ${ITK_LIBRARIES})

install(TARGETS ThinImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/ThinImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ThinImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThinImage)

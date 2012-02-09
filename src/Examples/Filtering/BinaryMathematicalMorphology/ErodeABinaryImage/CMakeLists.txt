cmake_minimum_required( VERSION 2.8 )

project( ErodeABinaryImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ErodeABinaryImage ErodeABinaryImage.cxx )
target_link_libraries( ErodeABinaryImage ${ITK_LIBRARIES} )

install( TARGETS ErodeABinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
)

install( FILES ErodeABinaryImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/ErodeABinaryImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ErodeABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ErodeABinaryImage ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png ErodeABinaryImageOutput.png 3
)

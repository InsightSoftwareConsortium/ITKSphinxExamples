cmake_minimum_required( VERSION 2.8.5 )

project( ErodeABinaryImage )

find_package( ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( ErodeABinaryImage Code.cxx )
target_link_libraries( ErodeABinaryImage ${ITK_LIBRARIES} )

install( TARGETS ErodeABinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/ErodeABinaryImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ErodeABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ErodeABinaryImage ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png Output.png 3
)

cmake_minimum_required( VERSION 2.8 )

project( DilateABinaryImage )

find_package( ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( DilateABinaryImage Code.cxx )
target_link_libraries( DilateABinaryImage ${ITK_LIBRARIES} )

install( TARGETS DilateABinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/DilateABinaryImage
  COMPONENT Code
)

enable_testing()
add_test( NAME DilateABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DilateABinaryImage ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png Output.png 3
  )

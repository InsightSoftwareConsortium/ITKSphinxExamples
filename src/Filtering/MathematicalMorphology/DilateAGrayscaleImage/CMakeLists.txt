cmake_minimum_required( VERSION 2.8.6 )

project( DilateAGrayscaleImage )

find_package( ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( DilateAGrayscaleImage Code.cxx )
target_link_libraries( DilateAGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS DilateAGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/MathematicalMorphology/DilateAGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME DilateAGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DilateAGrayscaleImage ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png Output.png 5
  )

cmake_minimum_required(VERSION 3.16.3)

project( CreateABinaryBallStructuringElement )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateABinaryBallStructuringElement Code.cxx )
target_link_libraries( CreateABinaryBallStructuringElement ${ITK_LIBRARIES} )

install( TARGETS CreateABinaryBallStructuringElement
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/CreateABinaryBallStructuringElement
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateABinaryBallStructuringElementTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateABinaryBallStructuringElement )

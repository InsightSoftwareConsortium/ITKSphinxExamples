cmake_minimum_required( VERSION 2.8 )

project( MersenneTwisterRandomIntegerGenerator )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( MersenneTwisterRandomIntegerGenerator MersenneTwisterRandomIntegerGenerator.cxx )
target_link_libraries( MersenneTwisterRandomIntegerGenerator ${ITK_LIBRARIES} )

install( TARGETS MersenneTwisterRandomIntegerGenerator
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES MersenneTwisterRandomIntegerGenerator.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MersenneTwisterRandomIntegerGenerator
  COMPONENT Code
)

enable_testing()
add_test( NAME MersenneTwisterRandomIntegerGeneratorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MersenneTwisterRandomIntegerGenerator )

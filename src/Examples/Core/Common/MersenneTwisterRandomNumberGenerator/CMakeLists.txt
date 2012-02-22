cmake_minimum_required( VERSION 2.8 )

project( MersenneTwisterRandomNumberGenerator )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( MersenneTwisterRandomNumberGenerator MersenneTwisterRandomNumberGenerator.cxx )
target_link_libraries( MersenneTwisterRandomNumberGenerator ${ITK_LIBRARIES} )

install( TARGETS MersenneTwisterRandomNumberGenerator
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES MersenneTwisterRandomNumberGenerator.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MersenneTwisterRandomNumberGenerator
  COMPONENT Code
)

enable_testing()
add_test( NAME MersenneTwisterRandomNumberGeneratorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MersenneTwisterRandomNumberGenerator )

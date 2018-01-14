cmake_minimum_required(VERSION 3.8.2)

project( MersenneTwisterRandomIntegerGenerator )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( MersenneTwisterRandomIntegerGenerator Code.cxx )
target_link_libraries( MersenneTwisterRandomIntegerGenerator ${ITK_LIBRARIES} )

install( TARGETS MersenneTwisterRandomIntegerGenerator
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MersenneTwisterRandomIntegerGenerator
  COMPONENT Code
)

enable_testing()
add_test( NAME MersenneTwisterRandomIntegerGeneratorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MersenneTwisterRandomIntegerGenerator )

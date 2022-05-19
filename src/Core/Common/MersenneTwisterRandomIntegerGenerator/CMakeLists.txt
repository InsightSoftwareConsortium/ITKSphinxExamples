cmake_minimum_required(VERSION 3.16.3)

project(MersenneTwisterRandomIntegerGenerator)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(MersenneTwisterRandomIntegerGenerator Code.cxx)
target_link_libraries(MersenneTwisterRandomIntegerGenerator ${ITK_LIBRARIES})

install(TARGETS MersenneTwisterRandomIntegerGenerator
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/MersenneTwisterRandomIntegerGenerator
  COMPONENT Code
)

enable_testing()
add_test(NAME MersenneTwisterRandomIntegerGeneratorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MersenneTwisterRandomIntegerGenerator)

cmake_minimum_required(VERSION 3.10.2)

project(ValuedRegionalMaximaImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ValuedRegionalMaximaImage Code.cxx)
target_link_libraries(ValuedRegionalMaximaImage ${ITK_LIBRARIES})

install(TARGETS ValuedRegionalMaximaImage
  DESTINATION bin/ITKExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/MathematicalMorphology/ValuedRegionalMaximaImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ValuedRegionalMaximaImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ValuedRegionalMaximaImage)

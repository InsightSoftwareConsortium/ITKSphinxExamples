cmake_minimum_required( VERSION 2.8.6 )

project( ApplyAtanImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAtanImageFilter Code.cxx )
target_link_libraries( ApplyAtanImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyAtanImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplyAtanImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAtanImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAtanImageFilter
    Output.mha
)

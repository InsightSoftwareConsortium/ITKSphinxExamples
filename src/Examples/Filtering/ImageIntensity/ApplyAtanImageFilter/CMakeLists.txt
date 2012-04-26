cmake_minimum_required( VERSION 2.8 )

project( ApplyAtanImageFilter )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ApplyAtanImageFilter ApplyAtanImageFilter.cxx )
target_link_libraries( ApplyAtanImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyAtanImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES ApplyAtanImageFilter.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplyAtanImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAtanImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAtanImageFilter
    ApplyAtanImageFilterOutput.mha
)

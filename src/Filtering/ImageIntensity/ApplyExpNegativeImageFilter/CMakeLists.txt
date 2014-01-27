cmake_minimum_required( VERSION 2.8 )

project( ApplyExpNegativeImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyExpNegativeImageFilter Code.cxx )
target_link_libraries( ApplyExpNegativeImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyExpNegativeImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplyExpNegativeImageFilter
  COMPONENT Code
  )

enable_testing()
add_test( NAME ApplyExpNegativeImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyExpNegativeImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.mha
    0.001
  )

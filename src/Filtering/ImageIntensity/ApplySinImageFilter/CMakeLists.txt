cmake_minimum_required( VERSION 2.8.5 )

project( ApplySinImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplySinImageFilter Code.cxx )
target_link_libraries( ApplySinImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplySinImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplySinImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplySinImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplySinImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Input.mha
    Output.mha
)

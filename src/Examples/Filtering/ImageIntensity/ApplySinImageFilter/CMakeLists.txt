cmake_minimum_required( VERSION 2.8 )

project( ApplySinImageFilter )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ApplySinImageFilter ApplySinImageFilter.cxx )
target_link_libraries( ApplySinImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplySinImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES ApplySinImageFilter.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplySinImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplySinImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplySinImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/ApplySinImageFilterInput.mha
    ApplySinImageFilterOutput.mha
)

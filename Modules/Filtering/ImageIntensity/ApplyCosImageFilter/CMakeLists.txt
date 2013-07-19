cmake_minimum_required( VERSION 2.8 )

project( ApplyCosImageFilter )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ApplyCosImageFilter Code.cxx )
target_link_libraries( ApplyCosImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyCosImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ApplyCosImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyCosImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyCosImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Input.mha
    Output.mha
)

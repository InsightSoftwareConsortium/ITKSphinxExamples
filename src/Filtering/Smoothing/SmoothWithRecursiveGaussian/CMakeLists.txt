cmake_minimum_required( VERSION 2.8.5 )

project( SmoothWithRecursiveGaussian )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SmoothWithRecursiveGaussian Code.cxx )
target_link_libraries( SmoothWithRecursiveGaussian ${ITK_LIBRARIES} )

install( TARGETS SmoothWithRecursiveGaussian
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/SmoothWithRecursiveGaussian
  COMPONENT Code
)

enable_testing()
add_test( NAME SmoothWithRecursiveGaussianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothWithRecursiveGaussian
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    3
)

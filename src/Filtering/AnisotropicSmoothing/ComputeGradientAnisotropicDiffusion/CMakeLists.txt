cmake_minimum_required( VERSION 2.8.5 )

project( ComputeGradientAnisotropicDiffusion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeGradientAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputeGradientAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputeGradientAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputeGradientAnisotropicDiffusion
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeGradientAnisotropicDiffusionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeGradientAnisotropicDiffusion
  ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
  Output.png
  5
  0.125
  1.0
)

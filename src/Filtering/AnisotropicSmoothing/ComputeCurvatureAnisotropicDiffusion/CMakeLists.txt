cmake_minimum_required( VERSION 2.8.5 )

project( ComputeCurvatureAnisotropicDiffusion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeCurvatureAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputeCurvatureAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputeCurvatureAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputeCurvatureAnisotropicDiffusion
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeCurvatureAnisotropicDiffusionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeCurvatureAnisotropicDiffusion
  ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
  Output.png
  5
  0.125
  3.0
)

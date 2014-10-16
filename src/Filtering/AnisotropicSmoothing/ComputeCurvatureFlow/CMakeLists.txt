cmake_minimum_required( VERSION 2.8.6 )

project( ComputeCurvatureFlow )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeCurvatureFlow Code.cxx )
target_link_libraries( ComputeCurvatureFlow ${ITK_LIBRARIES} )

install( TARGETS ComputeCurvatureFlow
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputeCurvatureFlow
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeCurvatureFlow
  ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
  Output.png
  5
  0.125
)

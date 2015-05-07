cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png )
set( output_image Output.png )
set( test_options 5 0.125 1.0 )

project( ComputeGradientAnisotropicDiffusion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeGradientAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputeGradientAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputeGradientAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputeGradientAnisotropicDiffusion
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeGradientAnisotropicDiffusionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeGradientAnisotropicDiffusion
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ComputeGradientAnisotropicDiffusionTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY ComputeGradientAnisotropicDiffusionTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ComputeGradientAnisotropicDiffusionTestHASPYTHONTEST FALSE )
endif()

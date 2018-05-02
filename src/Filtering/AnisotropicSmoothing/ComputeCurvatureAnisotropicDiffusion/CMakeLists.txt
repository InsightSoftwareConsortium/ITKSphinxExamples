cmake_minimum_required(VERSION 3.10.2)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png )
set( output_image Output.png )
set( test_options 5 0.125 3.0 )

project( ComputeCurvatureAnisotropicDiffusion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeCurvatureAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputeCurvatureAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputeCurvatureAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputeCurvatureAnisotropicDiffusion
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeCurvatureAnisotropicDiffusionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeCurvatureAnisotropicDiffusion
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ComputeCurvatureAnisotropicDiffusionTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

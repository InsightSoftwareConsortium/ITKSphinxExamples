cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image ComputePeronaMalikAnisotropicDiffusionTest.mha )
set( test_options 5 2.0 )

project( ComputePeronaMalikAnisotropicDiffusion )

find_package( ITK REQUIRED
  COMPONENTS
  ITKAnisotropicSmoothing
  ITKCommon
  ITKIOImageBase
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( ComputePeronaMalikAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputePeronaMalikAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputePeronaMalikAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputePeronaMalikAnisotropicDiffusion
  COMPONENT Code
)

enable_testing()

add_test( NAME ComputePeronaMalikAnisotropicDiffusionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputePeronaMalikAnisotropicDiffusion
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ComputePeronaMalikAnisotropicDiffusionTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY ComputePeronaMalikAnisotropicDiffusionTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ComputePeronaMalikAnisotropicDiffusionTestHASPYTHONTEST FALSE )
endif()

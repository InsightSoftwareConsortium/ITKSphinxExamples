cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image Output1X.png Output1Y.png Output2X.png Output2Y.png )

project( ApplyGradientRecursiveGaussianWithVectorInput )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyGradientRecursiveGaussianWithVectorInput Code.cxx )
target_link_libraries( ApplyGradientRecursiveGaussianWithVectorInput ${ITK_LIBRARIES} )

install( TARGETS ApplyGradientRecursiveGaussianWithVectorInput
  DESTINATION bin/ITKExamples/Filtering/ImageGradient/
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ApplyGradientRecursiveGaussianWithVectorInput
  COMPONENT Code
)

enable_testing()

add_test( NAME ApplyGradientRecursiveGaussianWithVectorInputTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyGradientRecursiveGaussianWithVectorInput
  ${input_image}
  ${output_image}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ApplyGradientRecursiveGaussianWithVectorInputTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
  )
  set_property( GLOBAL PROPERTY ApplyGradientRecursiveGaussianWithVectorInputTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ApplyGradientRecursiveGaussianWithVectorInputTestHASPYTHONTEST FALSE )
endif()

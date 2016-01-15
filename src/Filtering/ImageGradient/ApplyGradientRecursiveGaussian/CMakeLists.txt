cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image OutputX.png OutputY.png OutputMagnitude.png )

project( ApplyGradientRecursiveGaussian )

find_package( ITK 4.7.0 REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyGradientRecursiveGaussian Code.cxx )
target_link_libraries( ApplyGradientRecursiveGaussian ${ITK_LIBRARIES} )

install( TARGETS ApplyGradientRecursiveGaussian
  DESTINATION bin/ITKExamples/Filtering/ImageGradient/
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ApplyGradientRecursiveGaussian
  COMPONENT Code
)

enable_testing()

add_test( NAME ApplyGradientRecursiveGaussianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyGradientRecursiveGaussian
  ${input_image}
  ${output_image}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ApplyGradientRecursiveGaussianTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()

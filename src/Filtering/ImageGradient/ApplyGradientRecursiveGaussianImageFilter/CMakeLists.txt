cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image OutputX.png OutputY.png OutputMagnitude.png )

project( ApplyGradientRecursiveGaussianImageFilter )

find_package( ITK 4.7.0 REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyGradientRecursiveGaussianImageFilter Code.cxx )
target_link_libraries( ApplyGradientRecursiveGaussianImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyGradientRecursiveGaussianImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageGradient/
  COMPONENT Runtime
)

set( python_file )
if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  set( python_file Code.py )
endif()

install( FILES Code.cxx CMakeLists.txt ${python_file}
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ApplyGradientRecursiveGaussianImageFilter
  COMPONENT Code
)

enable_testing()

add_test( NAME ApplyGradientRecursiveGaussianImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyGradientRecursiveGaussianImageFilter
  ${input_image}
  ${output_image}
)

if( ITK_WRAP_PYTHON AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ApplyGradientRecursiveGaussianImageFilterTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
  )
  set_property( GLOBAL PROPERTY ApplyGradientRecursiveGaussianImageFilterTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ApplyGradientRecursiveGaussianImageFilterTestHASPYTHONTEST FALSE )
endif()

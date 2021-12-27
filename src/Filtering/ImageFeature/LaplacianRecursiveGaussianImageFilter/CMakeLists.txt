cmake_minimum_required(VERSION 3.16.3)

project( LaplacianRecursiveGaussianImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( LaplacianRecursiveGaussianImageFilter Code.cxx )
target_link_libraries( LaplacianRecursiveGaussianImageFilter ${ITK_LIBRARIES} )

install( TARGETS LaplacianRecursiveGaussianImageFilter
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/LaplacianRecursiveGaussianImageFilter
  COMPONENT Code
)

enable_testing()

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png )
set( output_image Output.mha )

add_test( NAME LaplacianRecursiveGaussianImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LaplacianRecursiveGaussianImageFilter
    ${input_image}
    ${output_image}
  )

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME LaplacianRecursiveGaussianImageFilterTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()

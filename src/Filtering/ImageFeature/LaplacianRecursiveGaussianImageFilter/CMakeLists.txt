cmake_minimum_required( VERSION 2.8.6 )

project( LaplacianRecursiveGaussianImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( LaplacianRecursiveGaussianImageFilter Code.cxx )
target_link_libraries( LaplacianRecursiveGaussianImageFilter ${ITK_LIBRARIES} )

install( TARGETS LaplacianRecursiveGaussianImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/LaplacianRecursiveGaussianImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME LaplacianRecursiveGaussianImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LaplacianRecursiveGaussianImageFilter
  ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
  Output.mha
  )

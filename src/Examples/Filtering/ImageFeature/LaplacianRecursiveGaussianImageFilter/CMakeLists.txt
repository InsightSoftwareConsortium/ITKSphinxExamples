cmake_minimum_required( VERSION 2.8 )

project( LaplacianRecursiveGaussianImageFilter )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( LaplacianRecursiveGaussianImageFilter LaplacianRecursiveGaussianImageFilter.cxx )
target_link_libraries( LaplacianRecursiveGaussianImageFilter ${ITK_LIBRARIES} )

install( TARGETS LaplacianRecursiveGaussianImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES LaplacianRecursiveGaussianImageFilter.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/LaplacianRecursiveGaussianImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME LaplacianRecursiveGaussianImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LaplacianRecursiveGaussianImageFilter )

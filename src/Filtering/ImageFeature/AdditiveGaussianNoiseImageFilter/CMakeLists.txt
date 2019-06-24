cmake_minimum_required(VERSION 3.10.2)

project( AdditiveGaussianNoiseImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( AdditiveGaussianNoiseImageFilter Code.cxx )
target_link_libraries( AdditiveGaussianNoiseImageFilter ${ITK_LIBRARIES} )

install( TARGETS AdditiveGaussianNoiseImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/AdditiveGaussianNoiseImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME AdditiveGaussianNoiseImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AdditiveGaussianNoiseImageFilter
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds8.png
  Output.mha
  )


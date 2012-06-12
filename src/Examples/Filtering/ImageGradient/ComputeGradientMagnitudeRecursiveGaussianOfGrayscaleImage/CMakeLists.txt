cmake_minimum_required( VERSION 2.8 )

project( ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage.cxx )
target_link_libraries( ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/ImageGradient
  COMPONENT Runtime
)

install( FILES ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ComputeGradientMagnitudeRecursiveGaussianOfGrayscaleImageTestOutput.mha
    2.
 )

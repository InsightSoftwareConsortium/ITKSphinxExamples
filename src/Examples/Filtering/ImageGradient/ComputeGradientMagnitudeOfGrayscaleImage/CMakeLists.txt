cmake_minimum_required( VERSION 2.8 )

project( ComputeGradientMagnitudeOfGrayscaleImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputeGradientMagnitudeOfGrayscaleImage ComputeGradientMagnitudeOfGrayscaleImage.cxx )
target_link_libraries( ComputeGradientMagnitudeOfGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ComputeGradientMagnitudeOfGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/ImageGradient
  COMPONENT Runtime
)

install( FILES ComputeGradientMagnitudeOfGrayscaleImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ComputeGradientMagnitudeOfGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeGradientMagnitudeOfGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeGradientMagnitudeOfGrayscaleImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ComputeGradientMagnitudeOfGrayscaleImageTestOutput.mha
    )

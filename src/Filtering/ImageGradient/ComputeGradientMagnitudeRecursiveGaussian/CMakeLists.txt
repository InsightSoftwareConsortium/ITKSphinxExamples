project( ComputeGradientMagnitudeRecursiveGaussian )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputeGradientMagnitudeRecursiveGaussian Code.cxx )
target_link_libraries( ComputeGradientMagnitudeRecursiveGaussian ${ITK_LIBRARIES} )

install( TARGETS ComputeGradientMagnitudeRecursiveGaussian
  DESTINATION bin/ITKExamples/Filtering/ImageGradient
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGradient/ComputeGradientMagnitudeRecursiveGaussian
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeGradientMagnitudeRecursiveGaussianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeGradientMagnitudeRecursiveGaussian
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ComputeGradientMagnitudeRecursiveGaussianTestOutput.mha
    2.
 )

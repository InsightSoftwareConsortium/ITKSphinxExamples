cmake_minimum_required(VERSION 3.10.2)

project( ComputeHistogramFromGrayscaleImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeHistogramFromGrayscaleImage Code.cxx )
target_link_libraries( ComputeHistogramFromGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ComputeHistogramFromGrayscaleImage
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/ComputeHistogramFromGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeHistogramFromGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeHistogramFromGrayscaleImage
    ${CMAKE_CURRENT_BINARY_DIR}/sf4.png
    16
  )

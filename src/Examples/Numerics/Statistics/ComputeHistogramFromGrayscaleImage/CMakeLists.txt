cmake_minimum_required( VERSION 2.8 )

project( ComputeHistogramFromGrayscaleImage )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( ComputeHistogramFromGrayscaleImage ComputeHistogramFromGrayscaleImage.cxx )
target_link_libraries( ComputeHistogramFromGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ComputeHistogramFromGrayscaleImage
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
)

install( FILES ComputeHistogramFromGrayscaleImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/ComputeHistogramFromGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( ComputeHistogramFromGrayscaleImageTest ComputeHistogramFromGrayscaleImage ${CMAKE_CURRENT_BINARY_DIR}/sf4.png 16 )

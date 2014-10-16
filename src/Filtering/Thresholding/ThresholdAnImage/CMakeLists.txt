cmake_minimum_required( VERSION 2.8.6 )

project( ThresholdAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ThresholdAnImage Code.cxx )
target_link_libraries( ThresholdAnImage ${ITK_LIBRARIES} )

install( TARGETS ThresholdAnImage
  DESTINATION bin/ITKExamples/Filtering/Thresholding
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Thresholding/ThresholdAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ThresholdAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThresholdAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output.png
    64
    128
)

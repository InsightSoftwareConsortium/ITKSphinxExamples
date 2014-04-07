cmake_minimum_required( VERSION 2.8.5 )

project( ThresholdAnImageUsingBinary )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ThresholdAnImageUsingBinary Code.cxx )
target_link_libraries( ThresholdAnImageUsingBinary ${ITK_LIBRARIES} )

install( TARGETS ThresholdAnImageUsingBinary
  DESTINATION bin/ITKExamples/Filtering/Thresholding
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Thresholding/ThresholdAnImageUsingBinary
  COMPONENT Code
)

enable_testing()
add_test( NAME ThresholdAnImageUsingBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThresholdAnImageUsingBinary
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    50
    150
    0
    255
)

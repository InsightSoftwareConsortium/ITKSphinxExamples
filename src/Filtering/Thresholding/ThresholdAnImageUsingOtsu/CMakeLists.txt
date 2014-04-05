project( ThresholdAnImageUsingOtsu )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ThresholdAnImageUsingOtsu Code.cxx )
target_link_libraries( ThresholdAnImageUsingOtsu ${ITK_LIBRARIES} )

install( TARGETS ThresholdAnImageUsingOtsu
  DESTINATION bin/ITKExamples/Filtering/Thresholding
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Thresholding/ThresholdAnImageUsingOtsu
  COMPONENT Code
)

enable_testing()
add_test( NAME ThresholdAnImageUsingOtsuTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThresholdAnImageUsingOtsu
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    64
    2
    1
)

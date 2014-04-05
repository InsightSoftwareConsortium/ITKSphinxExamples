project( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure Code.cxx )
target_link_libraries( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure ${ITK_LIBRARIES} )

install( TARGETS SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
  DESTINATION bin/ITKExamples/Nonunit/Review
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Nonunit/Review/SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
  COMPONENT Code
  )

enable_testing()
add_test( NAME SegmentBloodVesselsWithMultiScaleHessianBasedMeasureTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
    ${CMAKE_CURRENT_BINARY_DIR}/Sidestream_dark_field_image.png
    Output.png
    2.0
    6.0
    3
  )

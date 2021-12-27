cmake_minimum_required(VERSION 3.16.3)

project( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure Code.cxx )
target_link_libraries( SegmentBloodVesselsWithMultiScaleHessianBasedMeasure ${ITK_LIBRARIES} )

install( TARGETS SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
  DESTINATION bin/ITKSphinxExamples/Nonunit/Review
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Nonunit/Review/SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
  COMPONENT Code
  )

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Sidestream_dark_field_image.png)
set(output_image Output.png)
set(sigma_minimum 2.0)
set(sigma_maximum 6.0)
set(number_of_sigma_steps 3)

add_test( NAME SegmentBloodVesselsWithMultiScaleHessianBasedMeasureTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
    ${input_image}
    ${output_image}
    ${sigma_minimum}
    ${sigma_maximum}
    ${number_of_sigma_steps}
  )

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME SegmentBloodVesselsWithMultiScaleHessianBasedMeasureTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      --sigma_minimum ${sigma_minimum}
      --sigma_maximum ${sigma_maximum}
      --number_of_sigma_steps ${number_of_sigma_steps}
    )
endif()

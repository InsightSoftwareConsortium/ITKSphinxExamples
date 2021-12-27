cmake_minimum_required(VERSION 3.16.3)
project( ExtractGivenLabelObject )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ExtractGivenLabelObject Code.cxx )
target_link_libraries( ExtractGivenLabelObject ${ITK_LIBRARIES} )

install( TARGETS ExtractGivenLabelObject
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/ExtractGivenLabelObject
  COMPONENT Code
  )

enable_testing()
add_test( NAME ExtractGivenLabelObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractGivenLabelObject
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    Output1.png
    Output2.png
    100
)

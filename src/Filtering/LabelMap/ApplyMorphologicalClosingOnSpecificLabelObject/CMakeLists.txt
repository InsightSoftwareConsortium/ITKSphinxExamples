cmake_minimum_required(VERSION 3.8.2)
project( ApplyMorphologicalClosingOnSpecificLabelObject )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyMorphologicalClosingOnSpecificLabelObject Code.cxx )
target_link_libraries( ApplyMorphologicalClosingOnSpecificLabelObject ${ITK_LIBRARIES} )

install( TARGETS ApplyMorphologicalClosingOnSpecificLabelObject
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/ApplyMorphologicalClosingOnSpecificLabelObject
  COMPONENT Code
  )

enable_testing()
add_test( NAME ApplyMorphologicalClosingOnSpecificLabelObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyMorphologicalClosingOnSpecificLabelObject
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    Output.png
    100
    1
)

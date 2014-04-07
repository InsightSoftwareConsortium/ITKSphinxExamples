cmake_minimum_required( VERSION 2.8.5 )

project( MaskOneImageGivenLabelMap )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( MaskOneImageGivenLabelMap Code.cxx )
target_link_libraries( MaskOneImageGivenLabelMap ${ITK_LIBRARIES} )

install( TARGETS MaskOneImageGivenLabelMap
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/MaskOneImageGivenLabelMap
  COMPONENT Code
  )

enable_testing()
add_test( NAME MaskOneImageGivenLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MaskOneImageGivenLabelMap
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output1.png
    100
    0
)
add_test( NAME MaskOneImageGivenLabelMapTestNegateCrop
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MaskOneImageGivenLabelMap
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output2.png
    0
    0
    1
    1
    10
)

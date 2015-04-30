cmake_minimum_required( VERSION 2.8.6 )
project( OverlayLabelMapOnTopOfAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( OverlayLabelMapOnTopOfAnImage Code.cxx )
target_link_libraries( OverlayLabelMapOnTopOfAnImage ${ITK_LIBRARIES} )

install( TARGETS OverlayLabelMapOnTopOfAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageFusion
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFusion/OverlayLabelMapOnTopOfAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME OverlayLabelMapOnTopOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OverlayLabelMapOnTopOfAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ${CMAKE_CURRENT_BINARY_DIR}/label.png
    Output.png
)

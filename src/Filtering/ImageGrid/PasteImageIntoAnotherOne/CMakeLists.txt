cmake_minimum_required(VERSION 3.10.2)

project( PasteImageIntoAnotherOne )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( PasteImageIntoAnotherOne Code.cxx )
target_link_libraries( PasteImageIntoAnotherOne ${ITK_LIBRARIES} )

install( TARGETS PasteImageIntoAnotherOne
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/PasteImageIntoAnotherOne
  COMPONENT Code
  )

enable_testing()
add_test( NAME PasteImageIntoAnotherOneTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PasteImageIntoAnotherOne
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    20
    30
)

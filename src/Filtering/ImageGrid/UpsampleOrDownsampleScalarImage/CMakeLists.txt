cmake_minimum_required(VERSION 3.10.2)

project( UpsampleOrDownsampleScalarImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( UpsampleOrDownsampleScalarImage Code.cxx )
target_link_libraries( UpsampleOrDownsampleScalarImage ${ITK_LIBRARIES} )

install( TARGETS UpsampleOrDownsampleScalarImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/UpsampleOrDownsampleScalarImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME UpsampleOrDownsampleScalarImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UpsampleOrDownsampleScalarImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    160
    120
)

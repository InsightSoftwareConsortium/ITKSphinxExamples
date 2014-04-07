cmake_minimum_required( VERSION 2.8.5 )

project( PadAnImageWithAConstant )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( PadAnImageWithAConstant Code.cxx )
target_link_libraries( PadAnImageWithAConstant ${ITK_LIBRARIES} )

install( TARGETS PadAnImageWithAConstant
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/PadAnImageWithAConstant
  COMPONENT Code
)

enable_testing()
add_test( NAME PadAnImageWithAConstantTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PadAnImageWithAConstant
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    10
    50
    128
)

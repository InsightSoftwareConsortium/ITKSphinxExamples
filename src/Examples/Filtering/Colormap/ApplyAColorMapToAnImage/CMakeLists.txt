cmake_minimum_required( VERSION 2.8 )

project( ApplyAColorMapToAnImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ApplyAColorMapToAnImage Code.cxx )
target_link_libraries( ApplyAColorMapToAnImage ${ITK_LIBRARIES} )

install( TARGETS ApplyAColorMapToAnImage
  DESTINATION bin/ITKExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Colormap/ApplyAColorMapToAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAColorMapToAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAColorMapToAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
)

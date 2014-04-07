cmake_minimum_required( VERSION 2.8.5 )

project( RescaleAnImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( RescaleAnImage Code.cxx )
target_link_libraries( RescaleAnImage ${ITK_LIBRARIES} )

install( TARGETS RescaleAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/RescaleAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME RescaleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RescaleAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    0
    255
)

cmake_minimum_required(VERSION 3.10.2)

project( RescaleIntensity )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( RescaleIntensity Code.cxx )
target_link_libraries( RescaleIntensity ${ITK_LIBRARIES} )

install( TARGETS RescaleIntensity
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/RescaleIntensity
  COMPONENT Code
)

enable_testing()
add_test( NAME RescaleIntensityTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RescaleIntensity
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    0
    255
)

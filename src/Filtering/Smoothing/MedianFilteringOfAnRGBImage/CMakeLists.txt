cmake_minimum_required(VERSION 3.10.2)

project( MedianFilteringOfAnRGBImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( MedianFilteringOfAnRGBImage Code.cxx )
target_link_libraries( MedianFilteringOfAnRGBImage ${ITK_LIBRARIES} )

install( TARGETS MedianFilteringOfAnRGBImage
  DESTINATION bin/ITKSphinxExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Smoothing/MedianFilteringOfAnRGBImage
  COMPONENT Code
)

enable_testing()
add_test( NAME MedianFilteringOfAnRGBImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MedianFilteringOfAnRGBImage
    ${CMAKE_CURRENT_BINARY_DIR}/GourdsRGB.png
    Output.png
    2
)

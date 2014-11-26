cmake_minimum_required( VERSION 2.8.6 )
project( ExtractRegionOfInterestInOneImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ExtractRegionOfInterestInOneImage Code.cxx )
target_link_libraries( ExtractRegionOfInterestInOneImage ${ITK_LIBRARIES} )

install( TARGETS ExtractRegionOfInterestInOneImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/ExtractRegionOfInterestInOneImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ExtractRegionOfInterestInOneImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractRegionOfInterestInOneImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    50 150
    50 150
)

cmake_minimum_required(VERSION 3.10.2)

project( PermuteAxesOfAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( PermuteAxesOfAnImage Code.cxx )
target_link_libraries( PermuteAxesOfAnImage ${ITK_LIBRARIES} )

install( TARGETS PermuteAxesOfAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/PermuteAxesOfAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME PermuteAxesOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PermuteAxesOfAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
)

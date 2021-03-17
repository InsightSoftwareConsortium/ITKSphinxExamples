cmake_minimum_required(VERSION 3.10.2)

project( UpsampleAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( UpsampleAnImage Code.cxx )
target_link_libraries( UpsampleAnImage ${ITK_LIBRARIES} )

install( TARGETS UpsampleAnImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/UpsampleAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME UpsampleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UpsampleAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    2
    10)

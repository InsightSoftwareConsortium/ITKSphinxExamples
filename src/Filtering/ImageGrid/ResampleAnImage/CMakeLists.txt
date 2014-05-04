cmake_minimum_required( VERSION 2.8.5 )

project( ResampleAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ResampleAnImage Code.cxx )
target_link_libraries( ResampleAnImage ${ITK_LIBRARIES} )

install( TARGETS ResampleAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/ResampleAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ResampleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleAnImage
  ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
  Output.png
  2
)

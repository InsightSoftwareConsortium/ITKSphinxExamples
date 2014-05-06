cmake_minimum_required( VERSION 2.8.5 )

project( ComputeLaplacian )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeLaplacian Code.cxx )
target_link_libraries( ComputeLaplacian ${ITK_LIBRARIES} )

install( TARGETS ComputeLaplacian
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/ComputeLaplacian
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeLaplacianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeLaplacian
  ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
  Output.png
)

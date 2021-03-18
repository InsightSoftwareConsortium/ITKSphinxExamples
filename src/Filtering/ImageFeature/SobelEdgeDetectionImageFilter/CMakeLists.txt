cmake_minimum_required(VERSION 3.10.2)

project( SobelEdgeDetectionImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SobelEdgeDetectionImageFilter Code.cxx )
target_link_libraries( SobelEdgeDetectionImageFilter ${ITK_LIBRARIES} )

install( TARGETS SobelEdgeDetectionImageFilter
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/SobelEdgeDetectionImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME SobelEdgeDetectionImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SobelEdgeDetectionImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.mha
)

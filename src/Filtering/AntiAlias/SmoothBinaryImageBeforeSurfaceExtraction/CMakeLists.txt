cmake_minimum_required( VERSION 2.8 )

project( SmoothBinaryImageBeforeSurfaceExtraction )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SmoothBinaryImageBeforeSurfaceExtraction Code.cxx )
target_link_libraries( SmoothBinaryImageBeforeSurfaceExtraction ${ITK_LIBRARIES} )

install( TARGETS SmoothBinaryImageBeforeSurfaceExtraction
  DESTINATION bin/ITKExamples/Filtering/AntiAlias
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AntiAlias/SmoothBinaryImageBeforeSurfaceExtraction
  COMPONENT Code
  )

enable_testing()
add_test( NAME SmoothBinaryImageBeforeSurfaceExtractionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothBinaryImageBeforeSurfaceExtraction
    ${CMAKE_CURRENT_BINARY_DIR}/VentricleModel.png
    Output.mha
    0.001
    50
    2
    )

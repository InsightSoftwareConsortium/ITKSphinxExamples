project( SobelEdgeDetectionImageFilter )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( SobelEdgeDetectionImageFilter Code.cxx )
target_link_libraries( SobelEdgeDetectionImageFilter ${ITK_LIBRARIES} )

install( TARGETS SobelEdgeDetectionImageFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/SobelEdgeDetectionImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME SobelEdgeDetectionImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SobelEdgeDetectionImageFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.mha
)

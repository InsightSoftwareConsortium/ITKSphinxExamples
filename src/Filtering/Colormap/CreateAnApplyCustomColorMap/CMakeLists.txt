cmake_minimum_required( VERSION 2.8.6 )

project( CreateAnApplyCustomColorMap )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAnApplyCustomColorMap Code.cxx )
target_link_libraries( CreateAnApplyCustomColorMap ${ITK_LIBRARIES} )

install( TARGETS CreateAnApplyCustomColorMap
  DESTINATION bin/ITKExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Colormap/CreateAnApplyCustomColorMap
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAnApplyCustomColorMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnApplyCustomColorMap
  ${CMAKE_CURRENT_BINARY_DIR}/sf4.png
  Output.png
)

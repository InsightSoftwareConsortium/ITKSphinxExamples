cmake_minimum_required( VERSION 2.8.6 )
project( RemoveHolesNotConnectedToImageBoundaries )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( RemoveHolesNotConnectedToImageBoundaries Code.cxx )
target_link_libraries( RemoveHolesNotConnectedToImageBoundaries ${ITK_LIBRARIES} )

install( TARGETS RemoveHolesNotConnectedToImageBoundaries
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/RemoveHolesNotConnectedToImageBoundaries
  COMPONENT Code
  )

enable_testing()
add_test( NAME RemoveHolesNotConnectedToImageBoundariesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RemoveHolesNotConnectedToImageBoundaries
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png Output.png
)

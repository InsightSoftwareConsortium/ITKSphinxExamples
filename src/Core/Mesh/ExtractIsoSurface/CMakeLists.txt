cmake_minimum_required( VERSION 2.8.6 )

project( ExtractIsoSurface )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ExtractIsoSurface Code.cxx )
target_link_libraries( ExtractIsoSurface ${ITK_LIBRARIES} )

install( TARGETS ExtractIsoSurface
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/ExtractIsoSurface
  COMPONENT Code
  )

enable_testing()
add_test( NAME ExtractIsoSurfaceTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractIsoSurface
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    ${CMAKE_CURRENT_BINARY_DIR}/Output.vtk
    64
    255
)

cmake_minimum_required(VERSION 3.10.2)

project( GetListOfFacesAroundAGivenVertex )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( GetListOfFacesAroundAGivenVertex Code.cxx )
target_link_libraries( GetListOfFacesAroundAGivenVertex ${ITK_LIBRARIES} )

install( TARGETS GetListOfFacesAroundAGivenVertex
  DESTINATION bin/ITKExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/QuadEdgeMesh/GetListOfFacesAroundAGivenVertex
  COMPONENT Code
  )

enable_testing()
add_test( NAME GetListOfFacesAroundAGivenVertexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetListOfFacesAroundAGivenVertex ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk 0 )

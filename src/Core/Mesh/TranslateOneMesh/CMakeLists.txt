cmake_minimum_required( VERSION 2.8.6 )

project( TranslateOneMesh )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( TranslateOneMesh Code.cxx )
target_link_libraries( TranslateOneMesh ${ITK_LIBRARIES} )

install( TARGETS TranslateOneMesh
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/TranslateOneMesh
  COMPONENT Code
  )

enable_testing()
add_test( NAME TranslateOneMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TranslateOneMesh
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk
    ${CMAKE_CURRENT_BINARY_DIR}/Output.vtk

)

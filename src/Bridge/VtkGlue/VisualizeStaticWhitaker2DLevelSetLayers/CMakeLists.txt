cmake_minimum_required(VERSION 3.10.2)

project( VisualizeStaticWhitaker2DLevelSetLayers )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

find_package( VTK REQUIRED
  COMPONENTS
    vtkRenderingCore
    vtkRenderingGL2PSOpenGL2
  )
if( VTK_VERSION VERSION_LESS "8.90.0" )
  include( ${VTK_USE_FILE} )
endif()

add_executable( VisualizeStaticWhitaker2DLevelSetLayers Code.cxx )
target_link_libraries( VisualizeStaticWhitaker2DLevelSetLayers ${ITK_LIBRARIES} ${VTK_LIBRARIES} )

if( NOT VTK_VERSION VERSION_LESS "8.90.0" )
  vtk_module_autoinit(
    TARGETS VisualizeStaticWhitaker2DLevelSetLayers
    MODULES ${VTK_LIBRARIES}
    )
endif()

install( TARGETS VisualizeStaticWhitaker2DLevelSetLayers
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/VisualizeStaticWhitaker2DLevelSetLayers
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeStaticWhitaker2DLevelSetLayersTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeStaticWhitaker2DLevelSetLayers
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    0
  )

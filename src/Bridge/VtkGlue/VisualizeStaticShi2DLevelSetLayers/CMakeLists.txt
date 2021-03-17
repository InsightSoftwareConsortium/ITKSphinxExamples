cmake_minimum_required(VERSION 3.10.2)

project( VisualizeStaticShi2DLevelSetLayers )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

find_package(VTK REQUIRED)
set(_vtk_prefix "")
if(VTK_VERSION VERSION_LESS "8.90.0")
  set(_vtk_prefix "vtk")
endif()
find_package( VTK REQUIRED
  COMPONENTS
    ${_vtk_prefix}RenderingCore
    ${_vtk_prefix}RenderingGL2PSOpenGL2
  )
if( VTK_VERSION VERSION_LESS "8.90.0" )
  include( ${VTK_USE_FILE} )
endif()

add_executable( VisualizeStaticShi2DLevelSetLayers Code.cxx )
target_link_libraries( VisualizeStaticShi2DLevelSetLayers ${ITK_LIBRARIES} ${VTK_LIBRARIES} )

if( NOT VTK_VERSION VERSION_LESS "8.90.0" )
  vtk_module_autoinit(
    TARGETS VisualizeStaticShi2DLevelSetLayers
    MODULES ${VTK_LIBRARIES}
    )
endif()

install( TARGETS VisualizeStaticShi2DLevelSetLayers
  DESTINATION bin/ITKExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Bridge/VtkGlue/VisualizeStaticShi2DLevelSetLayers
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeStaticShi2DLevelSetLayersTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeStaticShi2DLevelSetLayers
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    0
  )

cmake_minimum_required(VERSION 3.16.3)

project(VTKImageToITKImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
set(_vtk_prefix "")
if(VTK_VERSION VERSION_LESS "8.90.0")
  set(_vtk_prefix "vtk")
endif()
find_package(VTK REQUIRED
  COMPONENTS
    ${_vtk_prefix}ImagingColor
    ${_vtk_prefix}IOImage
    ${_vtk_prefix}RenderingCore
    ${_vtk_prefix}RenderingGL2PSOpenGL2
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(VTKImageToITKImage Code.cxx)
target_link_libraries(VTKImageToITKImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS VTKImageToITKImage
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS VTKImageToITKImage
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/VTKImageToITKImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME VTKImageToITKImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VTKImageToITKImage Gourds.png)


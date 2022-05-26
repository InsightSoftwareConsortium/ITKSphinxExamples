cmake_minimum_required(VERSION 3.16.3)

project(InPlaceFilterOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
set(_vtk_prefix "")
if(VTK_VERSION VERSION_LESS "8.90.0")
  set(_vtk_prefix "vtk")
endif()
find_package(VTK REQUIRED
  COMPONENTS
    ${_vtk_prefix}InteractionImage
    ${_vtk_prefix}RenderingCore
    ${_vtk_prefix}RenderingGL2PSOpenGL2
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS InPlaceFilterOfImage
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/InPlaceFilterOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME InPlaceFilterOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} Gourds.png)

cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithNeighborhood)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED
  COMPONENTS
    vtkInteractionImage
    vtkRenderingCore
    vtkRenderingGL2PSOpenGL2
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(IterateRegionWithNeighborhood Code.cxx)
target_link_libraries(IterateRegionWithNeighborhood ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS IterateRegionWithNeighborhood
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS IterateRegionWithNeighborhood
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithNeighborhood/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithNeighborhoodTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithNeighborhood Yinyang.png)


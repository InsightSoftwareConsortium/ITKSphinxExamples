cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithWriteAccess)

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

add_executable(IterateRegionWithWriteAccess Code.cxx)
target_link_libraries(IterateRegionWithWriteAccess ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS IterateRegionWithWriteAccess
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS IterateRegionWithWriteAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithWriteAccess)

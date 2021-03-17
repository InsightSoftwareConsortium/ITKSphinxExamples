cmake_minimum_required(VERSION 3.10.2)

project(ConvertMeshToUnstructeredGrid)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED
  COMPONENTS
    vtkIOXML
    vtkCommonDataModel
    vtkInteractionImage
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(ConvertMeshToUnstructeredGrid Code.cxx)
target_link_libraries(ConvertMeshToUnstructeredGrid ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS WatchRegistration
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS ConvertMeshToUnstructeredGrid
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/ConvertMeshToUnstructeredGrid/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertMeshToUnstructeredGridTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertMeshToUnstructeredGrid)


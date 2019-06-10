cmake_minimum_required(VERSION 3.10.2)

project(ConvertMeshToUnstructeredGrid)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(ConvertMeshToUnstructeredGrid Code.cxx)
target_link_libraries(ConvertMeshToUnstructeredGrid ${ITK_LIBRARIES} ${VTK_LIBRARIES})

install(TARGETS ConvertMeshToUnstructeredGrid
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/ConvertMeshToUnstructeredGrid/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertMeshToUnstructeredGridTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertMeshToUnstructeredGrid)


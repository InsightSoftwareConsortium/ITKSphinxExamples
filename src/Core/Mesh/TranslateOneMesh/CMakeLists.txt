cmake_minimum_required(VERSION 3.22.1)

project(TranslateOneMesh)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKMeshIO
    ITK::ITKMeshModule
    ITK::ITKTransformModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/TranslateOneMesh
  COMPONENT Code
  )

enable_testing()
add_test(NAME TranslateOneMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk
    ${CMAKE_CURRENT_BINARY_DIR}/Output.vtk

)

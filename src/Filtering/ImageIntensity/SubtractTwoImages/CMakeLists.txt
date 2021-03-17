cmake_minimum_required(VERSION 3.10.2)

project(SubtractTwoImages)

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

add_executable(SubtractTwoImages Code.cxx)
target_link_libraries(SubtractTwoImages ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS SubtractTwoImages
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS SubtractTwoImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/SubtractTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SubtractTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SubtractTwoImages)


cmake_minimum_required(VERSION 3.10.2)

project(CropImageBySpecifyingRegion2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


if(ENABLE_QUICKVIEW)
  find_package(VTK REQUIRED
    COMPONENTS
      vtkRenderingCore
      vtkRenderingGL2PSOpenGL2
    )

  if(VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()

  add_executable(CropImageBySpecifyingRegion2 Code.cxx)
  target_link_libraries(CropImageBySpecifyingRegion2 ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS CropImageBySpecifyingRegion2
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(CropImageBySpecifyingRegion2 Code.cxx)
  target_link_libraries(CropImageBySpecifyingRegion2 ${ITK_LIBRARIES})
endif()

install(TARGETS CropImageBySpecifyingRegion2
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/CropImageBySpecifyingRegion2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CropImageBySpecifyingRegion2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CropImageBySpecifyingRegion2)

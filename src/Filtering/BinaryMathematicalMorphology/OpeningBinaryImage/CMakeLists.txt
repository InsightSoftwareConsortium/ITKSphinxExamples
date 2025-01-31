cmake_minimum_required(VERSION 3.22.1)

project(OpeningBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


if(ENABLE_QUICKVIEW)
  find_package(VTK REQUIRED
    COMPONENTS
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
      TARGETS OpeningBinaryImage
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})
endif()

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/OpeningBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME OpeningBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

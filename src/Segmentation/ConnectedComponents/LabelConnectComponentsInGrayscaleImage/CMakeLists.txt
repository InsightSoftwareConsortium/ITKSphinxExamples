cmake_minimum_required(VERSION 3.10.2)

project(LabelConnectComponentsInGrayscaleImage)

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

  add_executable(LabelConnectComponentsInGrayscaleImage Code.cxx)
  target_link_libraries(LabelConnectComponentsInGrayscaleImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS LabelConnectComponentsInGrayscaleImage
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(LabelConnectComponentsInGrayscaleImage Code.cxx)
  target_link_libraries(LabelConnectComponentsInGrayscaleImage ${ITK_LIBRARIES})
endif()

install(TARGETS LabelConnectComponentsInGrayscaleImage
  DESTINATION bin/ITKExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/ConnectedComponents/LabelConnectComponentsInGrayscaleImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelConnectComponentsInGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelConnectComponentsInGrayscaleImage)

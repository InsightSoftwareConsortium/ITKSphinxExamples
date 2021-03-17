cmake_minimum_required(VERSION 3.10.2)

project(ExtraLargestConnectComponentFromBinaryImage)

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

  add_executable(ExtraLargestConnectComponentFromBinaryImage Code.cxx)
  target_link_libraries(ExtraLargestConnectComponentFromBinaryImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ExtraLargestConnectComponentFromBinaryImage
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(ExtraLargestConnectComponentFromBinaryImage Code.cxx)
  target_link_libraries(ExtraLargestConnectComponentFromBinaryImage ${ITK_LIBRARIES})
endif()

install(TARGETS ExtraLargestConnectComponentFromBinaryImage
  DESTINATION bin/ITKSphinxExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Segmentation/ConnectedComponents/ExtraLargestConnectComponentFromBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtraLargestConnectComponentFromBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtraLargestConnectComponentFromBinaryImage
    Yinyang.png)

cmake_minimum_required(VERSION 3.10.2)

project(ZeroCrossingBasedEdgeDecor)

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

  add_executable(ZeroCrossingBasedEdgeDecor Code.cxx)
  target_link_libraries(ZeroCrossingBasedEdgeDecor ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ZeroCrossingBasedEdgeDecor
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(ZeroCrossingBasedEdgeDecor Code.cxx)
  target_link_libraries(ZeroCrossingBasedEdgeDecor ${ITK_LIBRARIES})
endif()

install(TARGETS ZeroCrossingBasedEdgeDecor
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/ZeroCrossingBasedEdgeDecor/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ZeroCrossingBasedEdgeDecorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ZeroCrossingBasedEdgeDecor
    Yinyang.png)

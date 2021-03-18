cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageWhilePreservingEdges2)

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

  add_executable(SmoothImageWhilePreservingEdges2 Code.cxx)
  target_link_libraries(SmoothImageWhilePreservingEdges2 ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS SmoothImageWhilePreservingEdges2
      MODULES ${VTK_LIBRARIES}
    )
  endif()
else()
  add_executable(SmoothImageWhilePreservingEdges2 Code.cxx)
  target_link_libraries(SmoothImageWhilePreservingEdges2 ${ITK_LIBRARIES})
endif()

install(TARGETS SmoothImageWhilePreservingEdges2
  DESTINATION bin/ITKSphinxExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/AnisotropicSmoothing/SmoothImageWhilePreservingEdges2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageWhilePreservingEdges2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageWhilePreservingEdges2
    Yinyang.png
    10
    30)

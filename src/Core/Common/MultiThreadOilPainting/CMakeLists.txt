cmake_minimum_required(VERSION 3.10.2)

project(MultiThreadOilPainting)

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

  add_executable(MultiThreadOilPainting Code.cxx)
  target_link_libraries(MultiThreadOilPainting ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS MultiThreadOilPainting
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(MultiThreadOilPainting Code.cxx)
  target_link_libraries(MultiThreadOilPainting ${ITK_LIBRARIES})
endif()

install(TARGETS MultiThreadOilPainting
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MultiThreadOilPainting/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultiThreadOilPaintingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiThreadOilPainting)

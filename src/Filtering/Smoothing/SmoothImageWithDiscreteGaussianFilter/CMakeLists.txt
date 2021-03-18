cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageWithDiscreteGaussianFilter)

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

  add_executable(SmoothImageWithDiscreteGaussianFilter Code.cxx)
  target_link_libraries(SmoothImageWithDiscreteGaussianFilter ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS SmoothImageWithDiscreteGaussianFilter
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(SmoothImageWithDiscreteGaussianFilter Code.cxx)
  target_link_libraries(SmoothImageWithDiscreteGaussianFilter ${ITK_LIBRARIES})
endif()

install(TARGETS SmoothImageWithDiscreteGaussianFilter
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/SmoothImageWithDiscreteGaussianFilter/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageWithDiscreteGaussianFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageWithDiscreteGaussianFilter
    Yinyang.png
    8)

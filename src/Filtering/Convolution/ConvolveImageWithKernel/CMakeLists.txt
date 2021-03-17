cmake_minimum_required(VERSION 3.10.2)

project(ConvolveImageWithKernel)

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

  add_executable(ConvolveImageWithKernel Code.cxx)
  target_link_libraries(ConvolveImageWithKernel ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ConvolveImageWithKernel
      MODULES ${VTK_LIBRARIES}
    )
  endif()
else()
  add_executable(ConvolveImageWithKernel Code.cxx)
  target_link_libraries(ConvolveImageWithKernel ${ITK_LIBRARIES})
endif()

install(TARGETS ConvolveImageWithKernel
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Convolution/ConvolveImageWithKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvolveImageWithKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvolveImageWithKernel
    Yinyang.png
    10)

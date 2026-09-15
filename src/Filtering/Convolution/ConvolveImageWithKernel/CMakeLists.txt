cmake_minimum_required(VERSION 3.22.1)

project(ConvolveImageWithKernel)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

if(ENABLE_QUICKVIEW)
  find_package(
    VTK
    REQUIRED
    COMPONENTS
      RenderingCore
      RenderingGL2PSOpenGL2
  )

  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKConvolutionModule
      ITK::ITKVtkGlueModule
      ${VTK_LIBRARIES}
  )

  vtk_module_autoinit(
    TARGETS ConvolveImageWithKernel
    MODULES ${VTK_LIBRARIES}
  )
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKConvolutionModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    Code.py
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/Convolution/ConvolveImageWithKernel/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ConvolveImageWithKernelTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} Yinyang.png 10
)

if(ITK_WRAP_PYTHON)
  add_test(
    NAME ConvolveImageWithKernelTestPython
    COMMAND
      ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png 10
  )
endif()

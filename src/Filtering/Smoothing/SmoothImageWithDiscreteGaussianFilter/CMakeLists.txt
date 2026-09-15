cmake_minimum_required(VERSION 3.22.1)

project(SmoothImageWithDiscreteGaussianFilter)

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
      ITK::ITKSmoothingModule
      ITK::ITKVtkGlueModule
      ${VTK_LIBRARIES}
  )

  vtk_module_autoinit(
    TARGETS SmoothImageWithDiscreteGaussianFilter
    MODULES ${VTK_LIBRARIES}
  )
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKSmoothingModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/Smoothing/SmoothImageWithDiscreteGaussianFilter/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME SmoothImageWithDiscreteGaussianFilterTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} Yinyang.png 8
)

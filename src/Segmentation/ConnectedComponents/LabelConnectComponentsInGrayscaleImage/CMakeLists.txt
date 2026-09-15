cmake_minimum_required(VERSION 3.22.1)

project(LabelConnectComponentsInGrayscaleImage)

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
      ITK::ITKConnectedComponentsModule
      ITK::ITKImageFusionModule
      ITK::ITKImageStatisticsModule
      ITK::ITKVtkGlueModule
      ${VTK_LIBRARIES}
  )

  vtk_module_autoinit(
    TARGETS LabelConnectComponentsInGrayscaleImage
    MODULES ${VTK_LIBRARIES}
  )
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKConnectedComponentsModule
      ITK::ITKImageFusionModule
      ITK::ITKImageStatisticsModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/ConnectedComponents
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Segmentation/ConnectedComponents/LabelConnectComponentsInGrayscaleImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME LabelConnectComponentsInGrayscaleImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

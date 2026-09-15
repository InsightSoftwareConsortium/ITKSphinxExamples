cmake_minimum_required(VERSION 3.22.1)

project(ClusterPixelsInGrayscaleImage)

find_package(ITK REQUIRED)

find_package(VTK REQUIRED)
find_package(
  VTK
  REQUIRED
  COMPONENTS
    InteractionImage
    RenderingCore
    RenderingGL2PSOpenGL2
)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKClassifiersModule
    ITK::ITKCommonModule
    ITK::ITKConnectedComponentsModule
    ITK::ITKImageIntensityModule
    ITK::ITKVtkGlueModule
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS ClusterPixelsInGrayscaleImage
  MODULES ${VTK_LIBRARIES}
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/Classifiers
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Segmentation/Classifiers/ClusterPixelsInGrayscaleImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ClusterPixelsInGrayscaleImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

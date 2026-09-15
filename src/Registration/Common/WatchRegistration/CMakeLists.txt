cmake_minimum_required(VERSION 3.22.1)

project(WatchRegistration)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

find_package(VTK REQUIRED)
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
    ITK::ITKImageCompareModule
    ITK::ITKImageGridModule
    ITK::ITKImageIntensityModule
    ITK::ITKOptimizersModule
    ITK::ITKRegistrationCommonModule
    ITK::ITKSmoothingModule
    ITK::ITKTransformModule
    ITK::ITKVtkGlueModule
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS WatchRegistration
  MODULES ${VTK_LIBRARIES}
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Registration/Common/WatchRegistration/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME WatchRegistrationTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} fixed.png moving.png
)

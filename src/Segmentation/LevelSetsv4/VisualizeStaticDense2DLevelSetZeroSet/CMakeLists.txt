cmake_minimum_required(VERSION 3.22.1)

project(VisualizeStaticDense2DLevelSetZeroSet)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKImageFeatureModule
    ITK::ITKImageIntensityModule
    ITK::ITKLevelSetsv4Module
    ITK::ITKThresholdingModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/LevelSetsv4
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Segmentation/LevelSetsv4/VisualizeStaticDense2DLevelSetZeroSet
  COMPONENT Code
)

enable_testing()
add_test(
  NAME VisualizeStaticDense2DLevelSetZeroSetTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png Output.png
)

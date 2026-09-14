cmake_minimum_required(VERSION 3.22.1)

project(VisualizeEvolvingDense2DLevelSetZeroSet)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKLevelSetsv4Module
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Bridge/VtkGlue/VisualizeEvolvingDense2DLevelSetZeroSet
  COMPONENT Code
)

enable_testing()
add_test(
  NAME VisualizeEvolvingDense2DLevelSetZeroSetTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png 100
)
set_tests_properties(
  VisualizeEvolvingDense2DLevelSetZeroSetTest
  PROPERTIES
    LABELS
      RUNS_LONG
)

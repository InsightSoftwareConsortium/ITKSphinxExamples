cmake_minimum_required(VERSION 3.22.1)

project(ConnectedComponentsInImage)

find_package(ITK REQUIRED)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
    ITK::ITKImageFilterBaseModule
    ITK::ITKRegionGrowingModule
    ITK::ITKVtkGlueModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/RegionGrowing
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Segmentation/RegionGrowing/ConnectedComponentsInImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ConnectedComponentsInImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

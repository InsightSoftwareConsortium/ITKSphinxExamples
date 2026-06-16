cmake_minimum_required(VERSION 3.22.1)

project(JoinImages)

find_package(ITK REQUIRED)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
    ITK::ITKImageAdaptorsModule
    ITK::ITKImageComposeModule
    ITK::ITKImageIntensityModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompose
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompose/JoinImages/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME JoinImagesTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

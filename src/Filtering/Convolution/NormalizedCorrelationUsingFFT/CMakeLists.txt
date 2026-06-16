cmake_minimum_required(VERSION 3.22.1)

project(NormalizedCorrelationUsingFFT)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKFFTModule
    ITK::ITKCommonModule
    ITK::ITKConvolutionModule
    ITK::ITKImageGridModule
    ITK::ITKImageIntensityModule
    ITK::ITKFFTImageFilterInit
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/Convolution/NormalizedCorrelationUsingFFT/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME NormalizedCorrelationUsingFFTTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

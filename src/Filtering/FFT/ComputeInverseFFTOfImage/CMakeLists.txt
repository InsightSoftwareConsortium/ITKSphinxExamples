cmake_minimum_required(VERSION 3.22.1)

project(ComputeInverseFFTOfImage)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKFFTModule
    ITK::ITKImageFilterBaseModule
    ITK::ITKImageIntensityModule
    ITK::ITKFFTImageFilterInit
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/FFT
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/FFT/ComputeInverseFFTOfImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ComputeInverseFFTOfImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)

if(ITK_WRAP_PYTHON)
  add_test(
    NAME ComputeInverseFFTOfImageTestPython
    COMMAND
      ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
  )
endif()

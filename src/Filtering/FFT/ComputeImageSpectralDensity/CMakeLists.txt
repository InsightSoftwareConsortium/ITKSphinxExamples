cmake_minimum_required(VERSION 3.16.3)

project(ComputeImageSpectralDensity)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ComputeImageSpectralDensity Code.cxx)
target_link_libraries(ComputeImageSpectralDensity ${ITK_LIBRARIES})

install(TARGETS ComputeImageSpectralDensity
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/ComputeImageSpectralDensity
  COMPONENT Code
  )

enable_testing()
add_test(NAME ComputeImageSpectralDensityTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeImageSpectralDensity
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    Output.mha
  )

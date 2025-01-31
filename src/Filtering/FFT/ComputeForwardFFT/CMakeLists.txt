cmake_minimum_required(VERSION 3.22.1)

project(ComputeForwardFFT)

find_package(ITK REQUIRED)

include(${ITK_USE_FILE})
add_executable(${PROJECT_NAME}
  Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/FFT
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/FFT/ComputeForwardFFT
  COMPONENT Code
  )

enable_testing()
add_test(NAME ComputeForwardFFTTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    OutputReal.mha
    OutputComplex.mha
    OutputModulus.mha
)

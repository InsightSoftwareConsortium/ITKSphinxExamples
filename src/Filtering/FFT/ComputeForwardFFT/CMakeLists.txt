cmake_minimum_required(VERSION 3.8.2)

project( ComputeForwardFFT )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputeForwardFFT
  Code.cxx )
target_link_libraries( ComputeForwardFFT ${ITK_LIBRARIES} )

install( TARGETS ComputeForwardFFT
  DESTINATION bin/ITKExamples/Filtering/FFT
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/FFT/ComputeForwardFFT
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeForwardFFTTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeForwardFFT
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    OutputReal.mha
    OutputComplex.mha
    OutputModulus.mha
)

cmake_minimum_required(VERSION 3.10.2)

project(NormalizedCorrelationUsingFFT)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizedCorrelationUsingFFT Code.cxx)
target_link_libraries(NormalizedCorrelationUsingFFT ${ITK_LIBRARIES})

install(TARGETS NormalizedCorrelationUsingFFT
  DESTINATION bin/ITKExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Convolution/NormalizedCorrelationUsingFFT/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NormalizedCorrelationUsingFFTTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizedCorrelationUsingFFT)

cmake_minimum_required(VERSION 3.10.2)

project(ComputeInverseFFTOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeInverseFFTOfImage Code.cxx)
target_link_libraries(ComputeInverseFFTOfImage ${ITK_LIBRARIES})

install(TARGETS ComputeInverseFFTOfImage
  DESTINATION bin/ITKSphinxExamples/Filtering/FFT
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/FFT/ComputeInverseFFTOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeInverseFFTOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeInverseFFTOfImage)

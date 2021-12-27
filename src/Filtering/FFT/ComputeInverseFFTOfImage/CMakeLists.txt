cmake_minimum_required(VERSION 3.16.3)

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

if(ITK_WRAP_PYTHON)
add_test(NAME ComputeInverseFFTOfImageTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

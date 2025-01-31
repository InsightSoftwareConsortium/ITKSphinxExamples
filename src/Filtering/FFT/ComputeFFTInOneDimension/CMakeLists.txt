cmake_minimum_required(VERSION 3.22.1)

project(ComputeFFTInOneDimension)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

install(FILES Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/FFT/ComputeFFTInOneDimension
  COMPONENT Code
  )

enable_testing()

if(ITK_WRAP_PYTHON)
  find_package(Python3 ${PYTHON_REQUIRED_VERSION} COMPONENTS Interpreter)
  add_test(NAME ComputeFFTInOneDimensionTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/MouseLiverRF.mha
      ${CMAKE_CURRENT_BINARY_DIR}/MouseLiver1DFFTModulusOutputPython.mha
      ${CMAKE_CURRENT_BINARY_DIR}/MouseLiver1DFFTPhaseOutputPython.mha
  )
endif()

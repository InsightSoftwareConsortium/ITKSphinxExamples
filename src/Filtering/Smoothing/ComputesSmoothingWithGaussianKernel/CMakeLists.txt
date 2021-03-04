cmake_minimum_required(VERSION 3.10.2)

project( ComputesSmoothingWithGaussianKernel )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputesSmoothingWithGaussianKernel Code.cxx )
target_link_libraries( ComputesSmoothingWithGaussianKernel ${ITK_LIBRARIES} )

install( TARGETS ComputesSmoothingWithGaussianKernel
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/ComputesSmoothingWithGaussianKernel
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputesSmoothingWithGaussianKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputesSmoothingWithGaussianKernel
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    3
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME ComputesSmoothingWithGaussianKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      OutputPython.png
      3
    )
endif()

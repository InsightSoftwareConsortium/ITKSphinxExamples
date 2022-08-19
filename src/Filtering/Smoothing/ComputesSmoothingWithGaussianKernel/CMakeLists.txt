cmake_minimum_required(VERSION 3.16.3)

project(ComputesSmoothingWithGaussianKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Smoothing/ComputesSmoothingWithGaussianKernel
  COMPONENT Code
)

enable_testing()
add_test(NAME ComputesSmoothingWithGaussianKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    3
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ComputesSmoothingWithGaussianKernelTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      OutputPython.png
      3
    )
endif()

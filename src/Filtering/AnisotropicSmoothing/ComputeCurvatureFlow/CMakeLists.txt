cmake_minimum_required(VERSION 3.16.3)

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options 5 0.125)

project(ComputeCurvatureFlow)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ComputeCurvatureFlow Code.cxx)
target_link_libraries(ComputeCurvatureFlow ${ITK_LIBRARIES})

install(TARGETS ComputeCurvatureFlow
  DESTINATION bin/ITKSphinxExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/AnisotropicSmoothing/ComputeCurvatureFlow
  COMPONENT Code
  )

enable_testing()
add_test(NAME ComputeCurvatureFlowTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeCurvatureFlow
  ${input_image}
  ${output_image}
  ${test_options}
)

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ComputeCurvatureFlowTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

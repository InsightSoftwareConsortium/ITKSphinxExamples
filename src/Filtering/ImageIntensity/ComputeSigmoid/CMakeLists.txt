cmake_minimum_required(VERSION 3.16.3)

project(ComputeSigmoid)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ComputeSigmoid Code.cxx)
target_link_libraries(ComputeSigmoid ${ITK_LIBRARIES})

install(TARGETS ComputeSigmoid
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/ComputeSigmoid
  COMPONENT Code
  )

enable_testing()
add_test(NAME ComputeSigmoidTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeSigmoid
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    10 240 10 170
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ComputeSigmoidTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      OutputPython.png
      10 240 10 170
    )
endif()

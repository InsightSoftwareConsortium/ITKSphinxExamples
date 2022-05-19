cmake_minimum_required(VERSION 3.16.3)

project(ThresholdAnImageUsingBinary)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ThresholdAnImageUsingBinary Code.cxx)
target_link_libraries(ThresholdAnImageUsingBinary ${ITK_LIBRARIES})

install(TARGETS ThresholdAnImageUsingBinary
  DESTINATION bin/ITKSphinxExamples/Filtering/Thresholding
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Thresholding/ThresholdAnImageUsingBinary
  COMPONENT Code
)

enable_testing()
add_test(NAME ThresholdAnImageUsingBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThresholdAnImageUsingBinary
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    50
    150
    0
    255
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ThresholdAnImageUsingBinaryTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      50
      150
      0
      255
    )
endif()

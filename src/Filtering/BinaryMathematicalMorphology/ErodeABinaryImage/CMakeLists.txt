cmake_minimum_required(VERSION 3.16.3)

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png)
set(output_image Output.png)
set(test_options 3)

project(ErodeABinaryImage)

find_package(ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include(${ITK_USE_FILE})

add_executable(ErodeABinaryImage Code.cxx)
target_link_libraries(ErodeABinaryImage ${ITK_LIBRARIES})

install(TARGETS ErodeABinaryImage
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology/
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/ErodeABinaryImage
  COMPONENT Code
)

enable_testing()

add_test(NAME ErodeABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ErodeABinaryImage
  ${input_image}
  ${output_image}
  ${test_options}
)

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ErodeABinaryImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

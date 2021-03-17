cmake_minimum_required( VERSION 3.10.2 )
project(DilateABinaryImage)


find_package(ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include(${ITK_USE_FILE})


add_executable(DilateABinaryImage Code.cxx)
target_link_libraries(DilateABinaryImage ${ITK_LIBRARIES})


install(TARGETS DilateABinaryImage
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology/
  COMPONENT Runtime
  )
install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/DilateABinaryImage
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png)
set(output_image Output.png)
set(test_options 3)

add_test(NAME DilateABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DilateABinaryImage
  ${input_image}
  ${output_image}
  ${test_options}
  )

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME DilateABinaryImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

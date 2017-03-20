cmake_minimum_required(VERSION 2.8.9)

project(ImageReadExtractFilterInsertWrite)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ImageReadExtractFilterInsertWrite Code.cxx)
target_link_libraries(ImageReadExtractFilterInsertWrite ${ITK_LIBRARIES})

install(TARGETS ImageReadExtractFilterInsertWrite
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Core/Common/ImageReadExtractFilterInsertWrite/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/105769fixed_B.nii.gz)
set(output_image Output.mha)
set(test_options 232) # slice number

add_test(NAME ImageReadExtractFilterInsertWriteTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImageReadExtractFilterInsertWrite
    ${input_image}
    ${output_image}
    ${test_options}
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ImageReadExtractFilterInsertWriteTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

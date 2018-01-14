cmake_minimum_required(VERSION 3.8.2)

project(WarpAnImageUsingADeformationField)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(WarpAnImageUsingADeformationField Code.cxx)
target_link_libraries(WarpAnImageUsingADeformationField ${ITK_LIBRARIES})

install(TARGETS WarpAnImageUsingADeformationField
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/WarpAnImageUsingADeformationField/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/WarpImageFilterInput.png)
set(displacement_field_image ${CMAKE_CURRENT_BINARY_DIR}/WarpImageFilterDisplacementField.mhd)
set(output_image Output.png)
set(test_options)

add_test(NAME WarpAnImageUsingADeformationFieldTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WarpAnImageUsingADeformationField
    ${input_image}
    ${displacement_field_image}
    ${output_image}
    ${test_options}
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME WarpAnImageUsingADeformationFieldTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${displacement_field_image}
      ${output_image}
      ${test_options}
    )
endif()

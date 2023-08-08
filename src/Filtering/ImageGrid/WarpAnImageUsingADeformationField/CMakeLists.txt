cmake_minimum_required(VERSION 3.16.3)

project(WarpAnImageUsingADeformationField)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/WarpAnImageUsingADeformationField/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/WarpImageFilterInput.png)
set(displacement_field_image ${CMAKE_CURRENT_BINARY_DIR}/WarpImageFilterDisplacementField.mhd)
set(output_image Output.png)
set(test_options)

add_test(NAME WarpAnImageUsingADeformationFieldTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${displacement_field_image}
    ${output_image}
    ${test_options}
  )

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME WarpAnImageUsingADeformationFieldTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${displacement_field_image}
      ${output_image}
      ${test_options}
    )
endif()

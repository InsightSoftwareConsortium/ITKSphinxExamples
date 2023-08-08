cmake_minimum_required(VERSION 3.16.3)

project(BlurringAnImageUsingABinomialKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Smoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Smoothing/BlurringAnImageUsingABinomialKernel/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png)
set(output_image Output.png)
set(test_options 5)

add_test(NAME BlurringAnImageUsingABinomialKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${output_image}
    ${test_options}
  )

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME BlurringAnImageUsingABinomialKernelTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

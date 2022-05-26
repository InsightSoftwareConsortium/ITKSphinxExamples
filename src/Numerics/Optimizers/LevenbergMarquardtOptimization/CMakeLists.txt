cmake_minimum_required(VERSION 3.16.3)

project(LevenbergMarquardtOptimization)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Numerics/Optimizers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Optimizers/LevenbergMarquardtOptimization/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options)

add_test(NAME LevenbergMarquardtOptimizationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${output_image}
    ${test_options}
  )

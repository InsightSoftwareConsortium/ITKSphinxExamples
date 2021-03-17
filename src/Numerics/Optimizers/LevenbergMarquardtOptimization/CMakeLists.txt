cmake_minimum_required(VERSION 3.10.2)

project(LevenbergMarquardtOptimization)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LevenbergMarquardtOptimization Code.cxx)
target_link_libraries(LevenbergMarquardtOptimization ${ITK_LIBRARIES})

install(TARGETS LevenbergMarquardtOptimization
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
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LevenbergMarquardtOptimization
    ${input_image}
    ${output_image}
    ${test_options}
  )

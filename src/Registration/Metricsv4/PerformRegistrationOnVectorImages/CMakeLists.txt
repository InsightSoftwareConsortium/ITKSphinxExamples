cmake_minimum_required(VERSION 3.16.3)

project(PerformRegistrationOnVectorImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Registration/Metricsv4
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Metricsv4/PerformRegistrationOnVectorImages/
  COMPONENT Code
  )


enable_testing()
set(fixed_image ${CMAKE_CURRENT_BINARY_DIR}/orange.jpg)
set(moving_image ${CMAKE_CURRENT_BINARY_DIR}/apple.jpg)
set(output_image Output.jpg)
set(test_options
  100
  25
  )

add_test(NAME PerformRegistrationOnVectorImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${fixed_image}
    ${moving_image}
    ${output_image}
    ${test_options}
  )

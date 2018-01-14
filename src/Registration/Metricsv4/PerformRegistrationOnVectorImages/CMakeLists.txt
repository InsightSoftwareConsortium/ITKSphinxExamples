cmake_minimum_required(VERSION 3.8.2)

project(PerformRegistrationOnVectorImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PerformRegistrationOnVectorImages Code.cxx)
target_link_libraries(PerformRegistrationOnVectorImages ${ITK_LIBRARIES})

install(TARGETS PerformRegistrationOnVectorImages
  DESTINATION bin/ITKExamples/Registration/Metricsv4
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Metricsv4/PerformRegistrationOnVectorImages/
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
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PerformRegistrationOnVectorImages
    ${fixed_image}
    ${moving_image}
    ${output_image}
    ${test_options}
  )

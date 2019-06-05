cmake_minimum_required(VERSION 3.10.2)

project(RequesterRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RequesterRegion Code.cxx)
target_link_libraries(RequesterRegion ${ITK_LIBRARIES})

install(TARGETS RequesterRegion
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/RequesterRegion/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options)

add_test(NAME RequesterRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RequesterRegion
    ${input_image}
    ${output_image}
    ${test_options}
  )

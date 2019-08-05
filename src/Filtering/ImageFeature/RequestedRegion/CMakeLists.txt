cmake_minimum_required(VERSION 3.10.2)

project(RequestedRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RequestedRegion Code.cxx)
target_link_libraries(RequestedRegion ${ITK_LIBRARIES})

install(TARGETS RequestedRegion
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/RequesderRegion/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options)

add_test(NAME RequestedRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RequestedRegion
    ${input_image}
    ${output_image}
    ${test_options}
  )

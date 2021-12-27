cmake_minimum_required(VERSION 3.16.3)

project(ApplyAFilterOnlyToASpecifiedImageRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ApplyAFilterOnlyToASpecifiedImageRegion Code.cxx)
target_link_libraries(ApplyAFilterOnlyToASpecifiedImageRegion ${ITK_LIBRARIES})

install(TARGETS ApplyAFilterOnlyToASpecifiedImageRegion
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/ApplyAFilterOnlyToASpecifiedImageRegion/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options)

add_test(NAME ApplyAFilterOnlyToASpecifiedImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAFilterOnlyToASpecifiedImageRegion
    ${input_image}
    ${output_image}
    ${test_options}
  )

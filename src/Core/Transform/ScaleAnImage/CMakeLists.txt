cmake_minimum_required(VERSION 3.10.2)

project(ScaleAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ScaleAnImage Code.cxx)
target_link_libraries(ScaleAnImage ${ITK_LIBRARIES})

install(TARGETS ScaleAnImage
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/ScaleAnImage/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/input.png)
set(output_image Output.png)
set(test_options)

add_test(NAME ScaleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ScaleAnImage
    ${input_image}
    ${output_image}
    ${test_options}
  )

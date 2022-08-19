cmake_minimum_required(VERSION 3.16.3)
project(SegmentBloodVessels)


find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})


install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )
install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/SegmentBloodVessels
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/HeadMRA.mha)
set(output_image Output.mha)
set(sigma 2.0)

add_test(NAME SegmentBloodVesselsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${output_image}
    ${sigma}
  )
set_tests_properties(SegmentBloodVesselsTest PROPERTIES LABELS RUNS_LONG)

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME SegmentBloodVesselsTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      --sigma ${sigma}
    )
  set_tests_properties(SegmentBloodVesselsTestPython PROPERTIES LABELS RUNS_LONG)
endif()

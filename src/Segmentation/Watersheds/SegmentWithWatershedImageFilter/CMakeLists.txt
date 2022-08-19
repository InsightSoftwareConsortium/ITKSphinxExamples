cmake_minimum_required(VERSION 3.16.3)

project(SegmentWithWatershedImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/Watersheds
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Segmentation/Watersheds/SegmentWithWatershedImageFilter/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(threshold01 0.0015)
set(threshold02 0.0025)
set(threshold03 0.005)
set(threshold04 0.0075)
set(threshold05 0.009)
set(level01 0.15)
set(level02 0.25)
set(level03 0.5)
set(level04 0.75)
set(level05 0.9)

add_test(NAME SegmentWithWatershedImageFilterTest01
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    SegmentWithWatershedImageFilterTest01.png
    ${threshold01}
    ${level01}
  )
add_test(NAME SegmentWithWatershedImageFilterTest02
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    SegmentWithWatershedImageFilterTest02.png
    ${threshold02}
    ${level02}
  )
add_test(NAME SegmentWithWatershedImageFilterTest03
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    SegmentWithWatershedImageFilterTest03.png
    ${threshold03}
    ${level03}
  )
add_test(NAME SegmentWithWatershedImageFilterTest04
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    SegmentWithWatershedImageFilterTest04.png
    ${threshold04}
    ${level04}
  )
add_test(NAME SegmentWithWatershedImageFilterTest05
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    SegmentWithWatershedImageFilterTest05.png
    ${threshold05}
    ${level05}
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME SegmentWithWatershedImageFilterTest01Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      SegmentWithWatershedImageFilterTest01Python.png
      ${threshold01}
      ${level01}
    )
  add_test(NAME SegmentWithWatershedImageFilterTest02Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      SegmentWithWatershedImageFilterTest02Python.png
      ${threshold02}
      ${level02}
    )
  add_test(NAME SegmentWithWatershedImageFilterTest03Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      SegmentWithWatershedImageFilterTest03Python.png
      ${threshold03}
      ${level03}
    )
  add_test(NAME SegmentWithWatershedImageFilterTest04Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      SegmentWithWatershedImageFilterTest04Python.png
      ${threshold04}
      ${level04}
    )
  add_test(NAME SegmentWithWatershedImageFilterTest05Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      SegmentWithWatershedImageFilterTest05Python.png
      ${threshold05}
      ${level05}
    )
endif()

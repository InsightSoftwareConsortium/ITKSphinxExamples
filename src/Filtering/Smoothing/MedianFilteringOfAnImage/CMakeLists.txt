cmake_minimum_required(VERSION 3.16.3)

project(MedianFilteringOfAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(MedianFilteringOfAnImage Code.cxx)
target_link_libraries(MedianFilteringOfAnImage ${ITK_LIBRARIES})

install(TARGETS MedianFilteringOfAnImage
  DESTINATION bin/ITKSphinxExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Smoothing/MedianFilteringOfAnImage
  COMPONENT Code
)

enable_testing()
add_test(NAME MedianFilteringOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MedianFilteringOfAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    2
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME MedianFilteringOfAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      2
    )
endif()

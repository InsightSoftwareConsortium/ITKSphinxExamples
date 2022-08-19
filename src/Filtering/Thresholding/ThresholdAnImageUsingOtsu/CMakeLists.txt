cmake_minimum_required(VERSION 3.16.3)

project(ThresholdAnImageUsingOtsu)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Thresholding
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Thresholding/ThresholdAnImageUsingOtsu
  COMPONENT Code
)

enable_testing()
add_test(NAME ThresholdAnImageUsingOtsuTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    64
    2
    1
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ThresholdAnImageUsingOtsuTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      64
      2
      1
    )
endif()

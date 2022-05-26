cmake_minimum_required(VERSION 3.16.3)

project(ComputeGradientMagnitude)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGradient
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGradient/ComputeGradientMagnitude
  COMPONENT Code
)

enable_testing()
add_test(NAME ComputeGradientMagnitudeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ComputeGradientMagnitudeTestOutput.mha
    )

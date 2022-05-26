cmake_minimum_required(VERSION 3.16.3)

project(MaskOneImageGivenLabelMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/MaskOneImageGivenLabelMap
  COMPONENT Code
  )

enable_testing()
add_test(NAME MaskOneImageGivenLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output1.png
    100
    0
)
add_test(NAME MaskOneImageGivenLabelMapTestNegateCrop
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output2.png
    0
    0
    1
    1
    10
)

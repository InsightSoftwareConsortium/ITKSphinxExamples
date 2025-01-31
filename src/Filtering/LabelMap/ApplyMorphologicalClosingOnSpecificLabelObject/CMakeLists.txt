cmake_minimum_required(VERSION 3.22.1)
project(ApplyMorphologicalClosingOnSpecificLabelObject)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/ApplyMorphologicalClosingOnSpecificLabelObject
  COMPONENT Code
  )

enable_testing()
add_test(NAME ApplyMorphologicalClosingOnSpecificLabelObjectTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    Output.png
    100
    1
)

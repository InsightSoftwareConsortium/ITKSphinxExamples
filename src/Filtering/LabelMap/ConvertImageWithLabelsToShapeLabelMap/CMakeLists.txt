cmake_minimum_required(VERSION 3.16.3)

project(ConvertImageWithLabelsToShapeLabelMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/ConvertImageWithLabelsToShapeLabelMap/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertImageWithLabelsToShapeLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
set_tests_properties(ConvertImageWithLabelsToShapeLabelMapTest
  PROPERTIES PASS_REGULAR_EXPRESSION "There are 2 objects.")

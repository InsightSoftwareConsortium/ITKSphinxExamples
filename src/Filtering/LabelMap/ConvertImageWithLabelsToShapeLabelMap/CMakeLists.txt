cmake_minimum_required(VERSION 3.16.3)

project(ConvertImageWithLabelsToShapeLabelMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertImageWithLabelsToShapeLabelMap Code.cxx)
target_link_libraries(ConvertImageWithLabelsToShapeLabelMap ${ITK_LIBRARIES})

install(TARGETS ConvertImageWithLabelsToShapeLabelMap
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/ConvertImageWithLabelsToShapeLabelMap/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertImageWithLabelsToShapeLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertImageWithLabelsToShapeLabelMap)

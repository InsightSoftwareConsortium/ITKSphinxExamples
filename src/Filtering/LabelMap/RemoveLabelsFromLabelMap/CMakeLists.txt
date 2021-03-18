cmake_minimum_required(VERSION 3.10.2)

project(RemoveLabelsFromLabelMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RemoveLabelsFromLabelMap Code.cxx)
target_link_libraries(RemoveLabelsFromLabelMap ${ITK_LIBRARIES})

install(TARGETS RemoveLabelsFromLabelMap
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/RemoveLabelsFromLabelMap/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RemoveLabelsFromLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RemoveLabelsFromLabelMap
  )

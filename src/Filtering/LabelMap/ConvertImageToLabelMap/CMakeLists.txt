cmake_minimum_required(VERSION 3.10.2)

project(ConvertImageToLabelMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertImageToLabelMap Code.cxx)
target_link_libraries(ConvertImageToLabelMap ${ITK_LIBRARIES})

install(TARGETS ConvertImageToLabelMap
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/ConvertImageToLabelMap/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertImageToLabelMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertImageToLabelMap)

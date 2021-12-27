cmake_minimum_required(VERSION 3.16.3)

project(LabelBinaryRegionsInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LabelBinaryRegionsInImage Code.cxx)
target_link_libraries(LabelBinaryRegionsInImage ${ITK_LIBRARIES})

install(TARGETS LabelBinaryRegionsInImage
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/LabelBinaryRegionsInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelBinaryRegionsInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelBinaryRegionsInImage)

cmake_minimum_required(VERSION 3.10.2)

project(LabelBinaryRegionsAndGetProperties)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LabelBinaryRegionsAndGetProperties Code.cxx)
target_link_libraries(LabelBinaryRegionsAndGetProperties ${ITK_LIBRARIES})

install(TARGETS LabelBinaryRegionsAndGetProperties
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/LabelBinaryRegionsAndGetProperties/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelBinaryRegionsAndGetPropertiesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelBinaryRegionsAndGetProperties)


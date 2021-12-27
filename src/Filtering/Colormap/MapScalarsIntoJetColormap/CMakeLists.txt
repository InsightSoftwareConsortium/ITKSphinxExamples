cmake_minimum_required(VERSION 3.16.3)

project(MapScalarsIntoJetColormap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MapScalarsIntoJetColormap Code.cxx)
target_link_libraries(MapScalarsIntoJetColormap ${ITK_LIBRARIES})

install(TARGETS MapScalarsIntoJetColormap
  DESTINATION bin/ITKSphinxExamples/Filtering/Colormap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Colormap/MapScalarsIntoJetColormap/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MapScalarsIntoJetColormapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MapScalarsIntoJetColormap)


cmake_minimum_required(VERSION 3.10.2)

project(OverlayLabelMapOnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(OverlayLabelMapOnImage Code.cxx)
target_link_libraries(OverlayLabelMapOnImage ${ITK_LIBRARIES})

install(TARGETS OverlayLabelMapOnImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFusion
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFusion/OverlayLabelMapOnImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME OverlayLabelMapOnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OverlayLabelMapOnImage)

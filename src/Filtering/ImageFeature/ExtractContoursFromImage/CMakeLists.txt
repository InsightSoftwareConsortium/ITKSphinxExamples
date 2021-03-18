cmake_minimum_required(VERSION 3.10.2)

project(ExtractContoursFromImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExtractContoursFromImage Code.cxx)
target_link_libraries(ExtractContoursFromImage ${ITK_LIBRARIES})

install(TARGETS ExtractContoursFromImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/ExtractContoursFromImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtractContoursFromImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractContoursFromImage)

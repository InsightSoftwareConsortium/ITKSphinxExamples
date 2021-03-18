cmake_minimum_required(VERSION 3.10.2)

project(ExtractChannelOfImageWithMultipleComponents)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExtractChannelOfImageWithMultipleComponents Code.cxx)
target_link_libraries(ExtractChannelOfImageWithMultipleComponents ${ITK_LIBRARIES})

install(TARGETS ExtractChannelOfImageWithMultipleComponents
  DESTINATION bin/ITKSphinxExamples/Core/ImageAdaptors
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageAdaptors/ExtractChannelOfImageWithMultipleComponents/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtractChannelOfImageWithMultipleComponentsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractChannelOfImageWithMultipleComponents)


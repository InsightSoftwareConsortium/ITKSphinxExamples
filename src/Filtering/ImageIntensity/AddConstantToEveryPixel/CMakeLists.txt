cmake_minimum_required(VERSION 3.16.3)

project(AddConstantToEveryPixel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AddConstantToEveryPixel Code.cxx)
target_link_libraries(AddConstantToEveryPixel ${ITK_LIBRARIES})

install(TARGETS AddConstantToEveryPixel
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/AddConstantToEveryPixel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AddConstantToEveryPixelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddConstantToEveryPixel)

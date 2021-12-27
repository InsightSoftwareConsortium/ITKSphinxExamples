cmake_minimum_required(VERSION 3.16.3)

project(SubtractConstantFromEveryPixel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SubtractConstantFromEveryPixel Code.cxx)
target_link_libraries(SubtractConstantFromEveryPixel ${ITK_LIBRARIES})

install(TARGETS SubtractConstantFromEveryPixel
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/SubtractConstantFromEveryPixel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SubtractConstantFromEveryPixelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SubtractConstantFromEveryPixel)


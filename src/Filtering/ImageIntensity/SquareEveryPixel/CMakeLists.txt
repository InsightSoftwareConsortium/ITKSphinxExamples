cmake_minimum_required(VERSION 3.10.2)

project(SquareEveryPixel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SquareEveryPixel Code.cxx)
target_link_libraries(SquareEveryPixel ${ITK_LIBRARIES})

install(TARGETS SquareEveryPixel
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/SquareEveryPixel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SquareEveryPixelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SquareEveryPixel)

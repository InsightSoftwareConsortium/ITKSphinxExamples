cmake_minimum_required(VERSION 3.16.3)

project(ComputeMedianOfImageAtPixel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeMedianOfImageAtPixel Code.cxx)
target_link_libraries(ComputeMedianOfImageAtPixel ${ITK_LIBRARIES})

install(TARGETS ComputeMedianOfImageAtPixel
  DESTINATION bin/ITKSphinxExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageFunction/ComputeMedianOfImageAtPixel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeMedianOfImageAtPixelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeMedianOfImageAtPixel

  )
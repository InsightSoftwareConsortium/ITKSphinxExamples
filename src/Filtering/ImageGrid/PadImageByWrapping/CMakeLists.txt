cmake_minimum_required(VERSION 3.10.2)

project(PadImageByWrapping)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PadImageByWrapping Code.cxx)
target_link_libraries(PadImageByWrapping ${ITK_LIBRARIES})

install(TARGETS PadImageByWrapping
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/PadImageByWrapping/
  COMPONENT Code
  )


enable_testing()
add_test(NAME PadImageByWrappingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PadImageByWrapping)


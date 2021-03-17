cmake_minimum_required(VERSION 3.10.2)

project(ShrinkImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ShrinkImage Code.cxx)
target_link_libraries(ShrinkImage ${ITK_LIBRARIES})

install(TARGETS ShrinkImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/ShrinkImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ShrinkImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ShrinkImage)


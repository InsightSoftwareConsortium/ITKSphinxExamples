cmake_minimum_required(VERSION 3.10.2)

project(RunImageFilterOnRegionOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RunImageFilterOnRegionOfImage Code.cxx)
target_link_libraries(RunImageFilterOnRegionOfImage ${ITK_LIBRARIES})

install(TARGETS RunImageFilterOnRegionOfImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/RunImageFilterOnRegionOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RunImageFilterOnRegionOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RunImageFilterOnRegionOfImage
        Yinyang.png
        10)

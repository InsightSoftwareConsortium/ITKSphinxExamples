cmake_minimum_required(VERSION 3.16.3)

project(IntensityWindowing)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IntensityWindowing Code.cxx)
target_link_libraries(IntensityWindowing ${ITK_LIBRARIES})

install(TARGETS IntensityWindowing
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/IntensityWindowing/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IntensityWindowingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IntensityWindowing)


cmake_minimum_required(VERSION 3.10.2)

project(IntensityWindowing)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IntensityWindowing Code.cxx)
target_link_libraries(IntensityWindowing ${ITK_LIBRARIES})

install(TARGETS IntensityWindowing
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/IntensityWindowing/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IntensityWindowingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IntensityWindowing)


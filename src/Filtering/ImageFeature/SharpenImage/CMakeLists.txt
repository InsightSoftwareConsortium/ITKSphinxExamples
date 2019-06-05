cmake_minimum_required(VERSION 3.10.2)

project(SharpenImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SharpenImage Code.cxx)
target_link_libraries(SharpenImage ${ITK_LIBRARIES})

install(TARGETS SharpenImage
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/SharpenImage/
  COMPONENT Code
  )

enable_testing()
add_test(NAME SharpenImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SharpenImage)


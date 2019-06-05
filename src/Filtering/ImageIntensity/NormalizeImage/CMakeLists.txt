cmake_minimum_required(VERSION 3.10.2)

project(NormalizeImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizeImage Code.cxx)
target_link_libraries(NormalizeImage ${ITK_LIBRARIES})

install(TARGETS NormalizeImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/NormalizeImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NormalizeImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizeImage)


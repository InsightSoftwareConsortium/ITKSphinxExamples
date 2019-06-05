cmake_minimum_required(VERSION 3.10.2)

project(AbsValueOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AbsValueOfImage Code.cxx)
target_link_libraries(AbsValueOfImage ${ITK_LIBRARIES})

install(TARGETS AbsValueOfImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/AbsValueOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AbsValueOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AbsValueOfImage)


cmake_minimum_required(VERSION 3.10.2)

project(DisplayImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DisplayImage Code.cxx)
target_link_libraries(DisplayImage ${ITK_LIBRARIES})

install(TARGETS DisplayImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/DisplayImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DisplayImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DisplayImage)

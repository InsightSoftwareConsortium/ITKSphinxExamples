cmake_minimum_required(VERSION 3.10.2)

project(FindMaxAndMinInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FindMaxAndMinInImage Code.cxx)
target_link_libraries(FindMaxAndMinInImage ${ITK_LIBRARIES})

install(TARGETS FindMaxAndMinInImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/FindMaxAndMinInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FindMaxAndMinInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FindMaxAndMinInImage)

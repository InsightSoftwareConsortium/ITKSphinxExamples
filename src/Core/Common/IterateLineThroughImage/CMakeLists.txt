cmake_minimum_required(VERSION 3.10.2)

project(IterateLineThroughImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateLineThroughImage Code.cxx)
target_link_libraries(IterateLineThroughImage ${ITK_LIBRARIES})

install(TARGETS IterateLineThroughImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateLineThroughImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateLineThroughImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateLineThroughImage)


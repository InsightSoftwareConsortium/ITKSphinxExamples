cmake_minimum_required(VERSION 3.16.3)

project(FilterImageUsingMultipleThreads)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FilterImageUsingMultipleThreads Code.cxx)
target_link_libraries(FilterImageUsingMultipleThreads ${ITK_LIBRARIES})

install(TARGETS FilterImageUsingMultipleThreads
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/FilterImageUsingMultipleThreads/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FilterImageUsingMultipleThreadsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FilterImageUsingMultipleThreads)


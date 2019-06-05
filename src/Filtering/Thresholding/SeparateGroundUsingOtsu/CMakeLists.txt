cmake_minimum_required(VERSION 3.10.2)

project(SeparateGroundUsingOtsu)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SeparateGroundUsingOtsu Code.cxx)
target_link_libraries(SeparateGroundUsingOtsu ${ITK_LIBRARIES})

install(TARGETS SeparateGroundUsingOtsu
  DESTINATION bin/ITKExamples/Filtering/Thresholding
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Thresholding/SeparateGroundUsingOtsu/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SeparateGroundUsingOtsuTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SeparateGroundUsingOtsu)


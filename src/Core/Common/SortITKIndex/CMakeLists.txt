cmake_minimum_required(VERSION 3.10.2)

project(SortITKIndex)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SortITKIndex Code.cxx)
target_link_libraries(SortITKIndex ${ITK_LIBRARIES})

install(TARGETS SortITKIndex
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/SortITKIndex/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SortITKIndexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SortITKIndex)


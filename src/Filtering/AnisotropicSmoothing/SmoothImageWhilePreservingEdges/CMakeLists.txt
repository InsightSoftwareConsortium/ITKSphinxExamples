cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageWhilePreservingEdges)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothImageWhilePreservingEdges Code.cxx)
target_link_libraries(SmoothImageWhilePreservingEdges ${ITK_LIBRARIES})

install(TARGETS SmoothImageWhilePreservingEdges
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/SmoothImageWhilePreservingEdges/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageWhilePreservingEdgesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageWhilePreservingEdges
    Yinyang.png
    4
    8)

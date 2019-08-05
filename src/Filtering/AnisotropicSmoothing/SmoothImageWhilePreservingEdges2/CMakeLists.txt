cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageWhilePreservingEdges2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothImageWhilePreservingEdges2 Code.cxx)
target_link_libraries(SmoothImageWhilePreservingEdges2 ${ITK_LIBRARIES})

install(TARGETS SmoothImageWhilePreservingEdges2
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/SmoothImageWhilePreservingEdges2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageWhilePreservingEdges2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageWhilePreservingEdges2
    Yinyang.png
    10
    30)

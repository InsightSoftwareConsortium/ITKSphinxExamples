cmake_minimum_required(VERSION 3.10.2)

project(WriteMeshToVTP)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(WriteMeshToVTP Code.cxx)
target_link_libraries(WriteMeshToVTP ${ITK_LIBRARIES})

install(TARGETS WriteMeshToVTP
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/WriteMeshToVTP/
  COMPONENT Code
  )


enable_testing()
add_test(NAME WriteMeshToVTPTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WriteMeshToVTP)

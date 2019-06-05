cmake_minimum_required(VERSION 3.10.2)

project(WorkingWithPointAndCellData)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(WorkingWithPointAndCellData Code.cxx)
target_link_libraries(WorkingWithPointAndCellData ${ITK_LIBRARIES})

install(TARGETS WorkingWithPointAndCellData
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/WorkingWithPointAndCellData/
  COMPONENT Code
  )


enable_testing()
add_test(NAME WorkingWithPointAndCellDataTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WorkingWithPointAndCellData)


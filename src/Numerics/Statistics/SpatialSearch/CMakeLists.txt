cmake_minimum_required(VERSION 3.10.2)

project(SpatialSearch)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SpatialSearch Code.cxx)
target_link_libraries(SpatialSearch ${ITK_LIBRARIES})

install(TARGETS SpatialSearch
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/SpatialSearch/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SpatialSearchTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SpatialSearch)

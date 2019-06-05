cmake_minimum_required(VERSION 3.10.2)

project(IterateWithNeighborhoodWithoutAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateWithNeighborhoodWithoutAccess Code.cxx)
target_link_libraries(IterateWithNeighborhoodWithoutAccess ${ITK_LIBRARIES})

install(TARGETS IterateWithNeighborhoodWithoutAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateWithNeighborhoodWithoutAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateWithNeighborhoodWithoutAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateWithNeighborhoodWithoutAccess)


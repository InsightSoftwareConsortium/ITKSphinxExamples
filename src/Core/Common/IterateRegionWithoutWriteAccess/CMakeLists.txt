cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithoutWriteAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateRegionWithoutWriteAccess Code.cxx)
target_link_libraries(IterateRegionWithoutWriteAccess ${ITK_LIBRARIES})

install(TARGETS IterateRegionWithoutWriteAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithoutWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithoutWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithoutWriteAccess)


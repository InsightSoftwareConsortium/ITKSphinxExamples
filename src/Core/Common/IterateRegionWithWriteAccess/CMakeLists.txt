cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithWriteAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateRegionWithWriteAccess Code.cxx)
target_link_libraries(IterateRegionWithWriteAccess ${ITK_LIBRARIES})

install(TARGETS IterateRegionWithWriteAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithWriteAccess)

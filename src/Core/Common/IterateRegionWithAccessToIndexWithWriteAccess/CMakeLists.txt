cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithAccessToIndexWithWriteAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateRegionWithAccessToIndexWithWriteAccess Code.cxx)
target_link_libraries(IterateRegionWithAccessToIndexWithWriteAccess ${ITK_LIBRARIES})

install(TARGETS IterateRegionWithAccessToIndexWithWriteAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithAccessToIndexWithWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithAccessToIndexWithWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithAccessToIndexWithWriteAccess)

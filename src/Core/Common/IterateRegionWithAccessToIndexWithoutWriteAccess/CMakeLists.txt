cmake_minimum_required(VERSION 3.10.2)

project(IterateRegionWithAccessToIndexWithoutWriteAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateRegionWithAccessToIndexWithoutWriteAccess Code.cxx)
target_link_libraries(IterateRegionWithAccessToIndexWithoutWriteAccess ${ITK_LIBRARIES})

install(TARGETS IterateRegionWithAccessToIndexWithoutWriteAccess
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateRegionWithAccessToIndexWithoutWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateRegionWithAccessToIndexWithoutWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateRegionWithAccessToIndexWithoutWriteAccess
    Yinyang.png)


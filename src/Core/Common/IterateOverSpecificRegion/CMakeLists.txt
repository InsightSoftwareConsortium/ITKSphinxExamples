cmake_minimum_required(VERSION 3.10.2)

project(IterateOverSpecificRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateOverSpecificRegion Code.cxx)
target_link_libraries(IterateOverSpecificRegion ${ITK_LIBRARIES})

install(TARGETS IterateOverSpecificRegion
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/IterateOverSpecificRegion/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateOverSpecificRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateOverSpecificRegion)

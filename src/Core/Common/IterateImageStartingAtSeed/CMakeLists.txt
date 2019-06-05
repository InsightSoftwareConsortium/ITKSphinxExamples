cmake_minimum_required(VERSION 3.10.2)

project(IterateImageStartingAtSeed)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateImageStartingAtSeed Code.cxx)
target_link_libraries(IterateImageStartingAtSeed ${ITK_LIBRARIES})

install(TARGETS IterateImageStartingAtSeed
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateImageStartingAtSeed/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateImageStartingAtSeedTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateImageStartingAtSeed)

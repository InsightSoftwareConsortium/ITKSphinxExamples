cmake_minimum_required(VERSION 3.10.2)

project(RandomSelectOfPixelsFromRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RandomSelectOfPixelsFromRegion Code.cxx)
target_link_libraries(RandomSelectOfPixelsFromRegion ${ITK_LIBRARIES})

install(TARGETS RandomSelectOfPixelsFromRegion
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/RandomSelectOfPixelsFromRegion/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RandomSelectOfPixelsFromRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RandomSelectOfPixelsFromRegion)

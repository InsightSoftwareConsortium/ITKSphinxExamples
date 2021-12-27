cmake_minimum_required(VERSION 3.16.3)

project(RandomSelectPixelFromRegionWithoutReplacee)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RandomSelectPixelFromRegionWithoutReplacee Code.cxx)
target_link_libraries(RandomSelectPixelFromRegionWithoutReplacee ${ITK_LIBRARIES})

install(TARGETS RandomSelectPixelFromRegionWithoutReplacee
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/RandomSelectPixelFromRegionWithoutReplacee/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RandomSelectPixelFromRegionWithoutReplaceeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RandomSelectPixelFromRegionWithoutReplacee)

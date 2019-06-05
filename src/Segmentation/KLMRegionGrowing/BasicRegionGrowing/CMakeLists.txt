cmake_minimum_required(VERSION 3.10.2)

project(BasicRegionGrowing)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BasicRegionGrowing Code.cxx)
target_link_libraries(BasicRegionGrowing ${ITK_LIBRARIES})

install(TARGETS BasicRegionGrowing
  DESTINATION bin/ITKExamples/Segmentation/KLMRegionGrowing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/KLMRegionGrowing/BasicRegionGrowing/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BasicRegionGrowingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BasicRegionGrowing)


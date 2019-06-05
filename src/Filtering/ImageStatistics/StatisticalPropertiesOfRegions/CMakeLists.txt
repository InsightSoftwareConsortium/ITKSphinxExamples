cmake_minimum_required(VERSION 3.10.2)

project(StatisticalPropertiesOfRegions)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(StatisticalPropertiesOfRegions Code.cxx)
target_link_libraries(StatisticalPropertiesOfRegions ${ITK_LIBRARIES})

install(TARGETS StatisticalPropertiesOfRegions
  DESTINATION bin/ITKExamples/Filtering/ImageStatistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageStatistics/StatisticalPropertiesOfRegions/
  COMPONENT Code
  )


enable_testing()
add_test(NAME StatisticalPropertiesOfRegionsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StatisticalPropertiesOfRegions)

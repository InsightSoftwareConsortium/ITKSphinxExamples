cmake_minimum_required(VERSION 3.16.3)

project(StatisticalPropertiesOfRegions)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(StatisticalPropertiesOfRegions Code.cxx)
target_link_libraries(StatisticalPropertiesOfRegions ${ITK_LIBRARIES})

install(TARGETS StatisticalPropertiesOfRegions
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageStatistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageStatistics/StatisticalPropertiesOfRegions/
  COMPONENT Code
  )


enable_testing()
add_test(NAME StatisticalPropertiesOfRegionsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StatisticalPropertiesOfRegions)

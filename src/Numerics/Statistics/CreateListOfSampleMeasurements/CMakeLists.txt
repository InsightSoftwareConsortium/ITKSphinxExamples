cmake_minimum_required(VERSION 3.16.3)

project(CreateListOfSampleMeasurements)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateListOfSampleMeasurements Code.cxx)
target_link_libraries(CreateListOfSampleMeasurements ${ITK_LIBRARIES})

install(TARGETS CreateListOfSampleMeasurements
  DESTINATION bin/ITKSphinxExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Statistics/CreateListOfSampleMeasurements/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateListOfSampleMeasurementsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateListOfSampleMeasurements)

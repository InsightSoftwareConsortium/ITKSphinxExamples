cmake_minimum_required(VERSION 3.16.3)

project(CreateListOfSamplesWithIDs)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateListOfSamplesWithIDs Code.cxx)
target_link_libraries(CreateListOfSamplesWithIDs ${ITK_LIBRARIES})

install(TARGETS CreateListOfSamplesWithIDs
  DESTINATION bin/ITKSphinxExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Statistics/CreateListOfSamplesWithIDs/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateListOfSamplesWithIDsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateListOfSamplesWithIDs)

cmake_minimum_required(VERSION 3.16.3)

project(KeepBinaryRegionsThatMeetSpecific)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(KeepBinaryRegionsThatMeetSpecific Code.cxx)
target_link_libraries(KeepBinaryRegionsThatMeetSpecific ${ITK_LIBRARIES})

install(TARGETS KeepBinaryRegionsThatMeetSpecific
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/KeepBinaryRegionsThatMeetSpecific/
  COMPONENT Code
  )


enable_testing()
add_test(NAME KeepBinaryRegionsThatMeetSpecificTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/KeepBinaryRegionsThatMeetSpecific
  )


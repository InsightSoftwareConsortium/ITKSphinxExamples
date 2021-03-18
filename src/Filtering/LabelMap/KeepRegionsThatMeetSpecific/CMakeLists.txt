cmake_minimum_required(VERSION 3.10.2)

project(KeepRegionsThatMeetSpecific)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(KeepRegionsThatMeetSpecific Code.cxx)
target_link_libraries(KeepRegionsThatMeetSpecific ${ITK_LIBRARIES})

install(TARGETS KeepRegionsThatMeetSpecific
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/KeepRegionsThatMeetSpecific/
  COMPONENT Code
  )


enable_testing()
add_test(NAME KeepRegionsThatMeetSpecificTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/KeepRegionsThatMeetSpecific
  )

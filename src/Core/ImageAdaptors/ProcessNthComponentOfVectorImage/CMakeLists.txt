cmake_minimum_required(VERSION 3.10.2)

project(ProcessNthComponentOfVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ProcessNthComponentOfVectorImage Code.cxx)
target_link_libraries(ProcessNthComponentOfVectorImage ${ITK_LIBRARIES})

install(TARGETS ProcessNthComponentOfVectorImage
  DESTINATION bin/ITKSphinxExamples/Core/ImageAdaptors
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageAdaptors/ProcessNthComponentOfVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ProcessNthComponentOfVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ProcessNthComponentOfVectorImage)

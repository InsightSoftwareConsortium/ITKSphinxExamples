cmake_minimum_required(VERSION 3.16.3)

project(FilterImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FilterImage Code.cxx)
target_link_libraries(FilterImage ${ITK_LIBRARIES})

install(TARGETS FilterImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/FilterImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FilterImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FilterImage)

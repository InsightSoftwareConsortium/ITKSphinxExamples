cmake_minimum_required(VERSION 3.16.3)

project(FilterImageWithoutCopying)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FilterImageWithoutCopying Code.cxx)
target_link_libraries(FilterImageWithoutCopying ${ITK_LIBRARIES})

install(TARGETS FilterImageWithoutCopying
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/FilterImageWithoutCopying/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FilterImageWithoutCopyingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FilterImageWithoutCopying)


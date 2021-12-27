cmake_minimum_required(VERSION 3.16.3)

project(BresenhamLine)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BresenhamLine Code.cxx)
target_link_libraries(BresenhamLine ${ITK_LIBRARIES})

install(TARGETS BresenhamLine
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/BresenhamLine/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BresenhamLineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BresenhamLine
  )

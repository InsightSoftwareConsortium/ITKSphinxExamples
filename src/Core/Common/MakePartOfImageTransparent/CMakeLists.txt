cmake_minimum_required(VERSION 3.10.2)

project(MakePartOfImageTransparent)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MakePartOfImageTransparent Code.cxx)
target_link_libraries(MakePartOfImageTransparent ${ITK_LIBRARIES})

install(TARGETS MakePartOfImageTransparent
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/MakePartOfImageTransparent/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MakePartOfImageTransparentTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MakePartOfImageTransparent
  )

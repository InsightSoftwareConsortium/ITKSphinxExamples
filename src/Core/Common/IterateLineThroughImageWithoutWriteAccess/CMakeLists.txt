cmake_minimum_required(VERSION 3.16.3)

project(IterateLineThroughImageWithoutWriteAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(IterateLineThroughImageWithoutWriteAccess Code.cxx)
target_link_libraries(IterateLineThroughImageWithoutWriteAccess ${ITK_LIBRARIES})

install(TARGETS IterateLineThroughImageWithoutWriteAccess
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/IterateLineThroughImageWithoutWriteAccess/
  COMPONENT Code
  )


enable_testing()
add_test(NAME IterateLineThroughImageWithoutWriteAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateLineThroughImageWithoutWriteAccess)


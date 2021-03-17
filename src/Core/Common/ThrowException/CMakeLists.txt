cmake_minimum_required(VERSION 3.10.2)

project(ThrowException)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ThrowException Code.cxx)
target_link_libraries(ThrowException ${ITK_LIBRARIES})

install(TARGETS ThrowException
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/ThrowException/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ThrowExceptionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThrowException)

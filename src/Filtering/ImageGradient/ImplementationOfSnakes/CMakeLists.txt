cmake_minimum_required(VERSION 3.16.3)

project(ImplementationOfSnakes)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ImplementationOfSnakes Code.cxx)
target_link_libraries(ImplementationOfSnakes ${ITK_LIBRARIES})

install(TARGETS ImplementationOfSnakes
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGradient
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGradient/ImplementationOfSnakes/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ImplementationOfSnakesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImplementationOfSnakes)

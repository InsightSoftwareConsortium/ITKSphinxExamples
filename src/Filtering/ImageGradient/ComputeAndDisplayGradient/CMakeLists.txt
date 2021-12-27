cmake_minimum_required(VERSION 3.16.3)

project(ComputeAndDisplayGradient)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeAndDisplayGradient Code.cxx)
target_link_libraries(ComputeAndDisplayGradient ${ITK_LIBRARIES})

install(TARGETS ComputeAndDisplayGradient
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGradient
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGradient/ComputeAndDisplayGradient/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeAndDisplayGradientTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeAndDisplayGradient)

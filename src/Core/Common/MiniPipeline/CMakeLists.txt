cmake_minimum_required(VERSION 3.10.2)

project(MiniPipeline)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MiniPipeline Code.cxx)
target_link_libraries(MiniPipeline ${ITK_LIBRARIES})

install(TARGETS MiniPipeline
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/MiniPipeline/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MiniPipelineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MiniPipeline)

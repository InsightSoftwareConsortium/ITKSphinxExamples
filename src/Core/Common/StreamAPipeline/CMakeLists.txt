cmake_minimum_required( VERSION 2.8.6 )

project( StreamAPipeline )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( StreamAPipeline Code.cxx )
target_link_libraries( StreamAPipeline ${ITK_LIBRARIES} )

install( TARGETS StreamAPipeline
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/StreamAPipeline
  COMPONENT Code
  )

enable_testing()
add_test( NAME StreamAPipelineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StreamAPipeline )

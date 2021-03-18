cmake_minimum_required(VERSION 3.10.2)

project( StreamAPipeline )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( StreamAPipeline Code.cxx )
target_link_libraries( StreamAPipeline ${ITK_LIBRARIES} )

install( TARGETS StreamAPipeline
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/StreamAPipeline
  COMPONENT Code
  )

enable_testing()
add_test( NAME StreamAPipelineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StreamAPipeline
    3
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME StreamAPipelineTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      3
    )
endif()

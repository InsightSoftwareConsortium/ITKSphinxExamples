cmake_minimum_required(VERSION 3.10.2)

project( ObserveAnEvent )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ObserveAnEvent Code.cxx )
target_link_libraries( ObserveAnEvent ${ITK_LIBRARIES} )

install( TARGETS ObserveAnEvent
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/ObserveAnEvent
  COMPONENT Code
)

enable_testing()
add_test( NAME ObserveAnEventTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ObserveAnEvent )

if( ITK_WRAP_PYTHON )
  add_test( NAME ObserveAnEventTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

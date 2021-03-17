cmake_minimum_required(VERSION 3.10.2)

project( BuildAHelloWorldProgram )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( BuildAHelloWorldProgram Code.cxx Code.py )
target_link_libraries( BuildAHelloWorldProgram ${ITK_LIBRARIES} )

install( TARGETS BuildAHelloWorldProgram
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/BuildAHelloWorldProgram
  COMPONENT Code
)

enable_testing()
add_test( NAME BuildAHelloWorldProgramTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BuildAHelloWorldProgram )

if(ITK_WRAP_PYTHON)
  add_test(NAME BuildAHelloWorldProgramTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

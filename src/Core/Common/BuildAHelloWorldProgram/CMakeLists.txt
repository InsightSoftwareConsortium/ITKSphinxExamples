project( BuildAHelloWorldProgram )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( BuildAHelloWorldProgram Code.cxx )
target_link_libraries( BuildAHelloWorldProgram ${ITK_LIBRARIES} )

install( TARGETS BuildAHelloWorldProgram
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/BuildAHelloWorldProgram
  COMPONENT Code
)

enable_testing()
add_test( NAME BuildAHelloWorldProgramTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BuildAHelloWorldProgram )

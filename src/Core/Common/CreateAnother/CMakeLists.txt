project( CreateAnother )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAnother Code.cxx )
target_link_libraries( CreateAnother ${ITK_LIBRARIES} )

install( TARGETS CreateAnother
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAnother
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAnotherTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnother )

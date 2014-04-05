project( CreateAIndex )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAIndex Code.cxx )
target_link_libraries( CreateAIndex ${ITK_LIBRARIES} )

install( TARGETS CreateAIndex
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAIndex
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAIndexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAIndex )

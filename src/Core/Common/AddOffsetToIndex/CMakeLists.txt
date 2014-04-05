project( AddOffsetToIndex )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( AddOffsetToIndex Code.cxx )
target_link_libraries( AddOffsetToIndex ${ITK_LIBRARIES} )

install( TARGETS AddOffsetToIndex
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/AddOffsetToIndex
  COMPONENT Code
)

enable_testing()
add_test( NAME AddOffsetToIndexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddOffsetToIndex )

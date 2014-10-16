cmake_minimum_required( VERSION 2.8.6 )

project( CreateAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAPointSet Code.cxx )
target_link_libraries( CreateAPointSet ${ITK_LIBRARIES} )

install( TARGETS CreateAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAPointSet
)

cmake_minimum_required( VERSION 2.8 )

project( CreateAVector )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAVector Code.cxx )
target_link_libraries( CreateAVector ${ITK_LIBRARIES} )

install( TARGETS CreateAVector
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAVector
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAVector )

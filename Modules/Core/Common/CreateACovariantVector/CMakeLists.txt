cmake_minimum_required( VERSION 2.8 )

project( CreateACovariantVector )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CreateACovariantVector Code.cxx )
target_link_libraries( CreateACovariantVector ${ITK_LIBRARIES} )

install( TARGETS CreateACovariantVector
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateACovariantVector
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateACovariantVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateACovariantVector )

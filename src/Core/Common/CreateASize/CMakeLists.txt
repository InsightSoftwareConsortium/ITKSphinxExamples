cmake_minimum_required( VERSION 2.8.5 )

project( CreateASize )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateASize Code.cxx )
target_link_libraries( CreateASize ${ITK_LIBRARIES} )

install( TARGETS CreateASize
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateASize
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateASizeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateASize )

cmake_minimum_required( VERSION 2.8.5 )

project( WriteAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( WriteAnImage Code.cxx )
target_link_libraries( WriteAnImage ${ITK_LIBRARIES} )

install( TARGETS WriteAnImage
  DESTINATION bin/ITKExamples/Base/
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Base//WriteAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME WriteAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WriteAnImage )

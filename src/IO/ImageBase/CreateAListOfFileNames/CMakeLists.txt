cmake_minimum_required( VERSION 2.8.5 )

project( CreateAListOfFileNames )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAListOfFileNames Code.cxx )
target_link_libraries( CreateAListOfFileNames ${ITK_LIBRARIES} )

install( TARGETS CreateAListOfFileNames
  DESTINATION bin/ITKExamples/IO/ImageBase
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/ImageBase/CreateAListOfFileNames
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAListOfFileNamesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAListOfFileNames )

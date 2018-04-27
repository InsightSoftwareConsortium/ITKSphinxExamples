cmake_minimum_required(VERSION 3.10.2)

project( DuplicateAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DuplicateAnImage Code.cxx )
target_link_libraries( DuplicateAnImage ${ITK_LIBRARIES} )

install( TARGETS DuplicateAnImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/DuplicateAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME DuplicateAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DuplicateAnImage )

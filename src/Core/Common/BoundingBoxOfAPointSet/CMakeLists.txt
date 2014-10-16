cmake_minimum_required( VERSION 2.8.6 )

project( BoundingBoxOfAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( BoundingBoxOfAPointSet Code.cxx )
target_link_libraries( BoundingBoxOfAPointSet ${ITK_LIBRARIES} )

install( TARGETS BoundingBoxOfAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/BoundingBoxOfAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME BoundingBoxOfAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BoundingBoxOfAPointSet )

cmake_minimum_required( VERSION 2.8 )

project( BoundingBoxOfAPointSet )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( BoundingBoxOfAPointSet BoundingBoxOfAPointSet.cxx )
target_link_libraries( BoundingBoxOfAPointSet ${ITK_LIBRARIES} )

install( TARGETS BoundingBoxOfAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES BoundingBoxOfAPointSet.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/BoundingBoxOfAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME BoundingBoxOfAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BoundingBoxOfAPointSet )

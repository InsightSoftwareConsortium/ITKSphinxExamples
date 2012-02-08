cmake_minimum_required( VERSION 2.8 )

project( ReadAPointSet )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( ReadAPointSet ReadAPointSet.cxx )
target_link_libraries( ReadAPointSet ${ITK_LIBRARIES} )

install( TARGETS ReadAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

enable_testing()
add_test( ReadAPointSetTest ReadAPointSet )

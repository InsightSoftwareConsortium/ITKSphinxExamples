cmake_minimum_required( VERSION 2.8 )

project( CreateAPointSet )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CreateAPointSet CreateAPointSet.cxx )
target_link_libraries( CreateAPointSet ${ITK_LIBRARIES} )

enable_testing()
add_test( CreateAPointSetTest CreateAPointSet )

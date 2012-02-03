cmake_minimum_required( VERSION 2.8 )

project( DoDataParallelThreading )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DoDataParallelThreading DoDataParallelThreading.cxx )
target_link_libraries( DoDataParallelThreading ${ITK_LIBRARIES} )

enable_testing()
add_test( DoDataParallelThreadingTest DoDataParallelThreading )

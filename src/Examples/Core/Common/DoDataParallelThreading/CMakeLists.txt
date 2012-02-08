cmake_minimum_required( VERSION 2.8 )

project( DoDataParallelThreading )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DoDataParallelThreading DoDataParallelThreading.cxx )
target_link_libraries( DoDataParallelThreading ${ITK_LIBRARIES} )

install( TARGETS DoDataParallelThreading
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

enable_testing()
add_test( DoDataParallelThreadingTest DoDataParallelThreading )

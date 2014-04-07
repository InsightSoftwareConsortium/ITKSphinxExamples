cmake_minimum_required( VERSION 2.8.5 )

project( CopyACompositeTransform )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CopyACompositeTransform Code.cxx )
target_link_libraries( CopyACompositeTransform ${ITK_LIBRARIES} )

install( TARGETS CopyACompositeTransform
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/CopyACompositeTransform
  COMPONENT Code
  )

enable_testing()
add_test( NAME CopyACompositeTransformTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CopyACompositeTransform )

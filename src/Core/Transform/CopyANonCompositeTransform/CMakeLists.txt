project( CopyANonCompositeTransform )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CopyANonCompositeTransform Code.cxx )
target_link_libraries( CopyANonCompositeTransform ${ITK_LIBRARIES} )

install( TARGETS CopyANonCompositeTransform
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/CopyANonCompositeTransform
  COMPONENT Code
  )

enable_testing()
add_test( NAME CopyANonCompositeTransformTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CopyANonCompositeTransform )

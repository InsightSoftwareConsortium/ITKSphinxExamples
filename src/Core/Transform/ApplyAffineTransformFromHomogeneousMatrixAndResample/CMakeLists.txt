cmake_minimum_required( VERSION 2.8.5 )
project( ApplyAffineTransformFromHomogeneousMatrixAndResample )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAffineTransformFromHomogeneousMatrixAndResample Code.cxx )
target_link_libraries( ApplyAffineTransformFromHomogeneousMatrixAndResample ${ITK_LIBRARIES} )

install( TARGETS ApplyAffineTransformFromHomogeneousMatrixAndResample
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/ApplyAffineTransformFromHomogeneousMatrixAndResample
  COMPONENT Code
  )

enable_testing()
add_test( NAME ApplyAffineTransformFromHomogeneousMatrixAndResampleTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAffineTransformFromHomogeneousMatrixAndResample
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    0
)

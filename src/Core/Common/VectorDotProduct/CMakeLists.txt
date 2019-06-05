cmake_minimum_required(VERSION 3.10.2)

project( VectorDotProduct )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( VectorDotProduct Code.cxx )
target_link_libraries( VectorDotProduct ${ITK_LIBRARIES} )

install( TARGETS VectorDotProduct
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/VectorDotProduct
  COMPONENT Code
)

enable_testing()
add_test( NAME VectorDotProductTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VectorDotProduct )

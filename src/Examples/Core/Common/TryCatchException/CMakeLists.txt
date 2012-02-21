cmake_minimum_required( VERSION 2.8 )

project( TryCatchException )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( TryCatchException TryCatchException.cxx )
target_link_libraries( TryCatchException ${ITK_LIBRARIES} )

install( TARGETS TryCatchException
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES TryCatchException.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/TryCatchException
  COMPONENT Code
)

enable_testing()
add_test( NAME TryCatchExceptionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TryCatchException )

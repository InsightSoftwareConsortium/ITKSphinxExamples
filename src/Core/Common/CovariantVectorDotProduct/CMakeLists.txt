project( CovariantVectorDotProduct )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CovariantVectorDotProduct Code.cxx )
target_link_libraries( CovariantVectorDotProduct ${ITK_LIBRARIES} )

install( TARGETS CovariantVectorDotProduct
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CovariantVectorDotProduct
  COMPONENT Code
)

enable_testing()
add_test( NAME CovariantVectorDotProductTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CovariantVectorDotProduct )

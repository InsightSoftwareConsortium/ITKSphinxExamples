cmake_minimum_required( VERSION 2.8.5 )

project( CovariantVectorNorm )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CovariantVectorNorm Code.cxx )
target_link_libraries( CovariantVectorNorm ${ITK_LIBRARIES} )

install( TARGETS CovariantVectorNorm
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CovariantVectorNorm
  COMPONENT Code
)

enable_testing()
add_test( NAME CovariantVectorNormTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CovariantVectorNorm )

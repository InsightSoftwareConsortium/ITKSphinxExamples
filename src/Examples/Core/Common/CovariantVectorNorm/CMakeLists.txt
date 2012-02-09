cmake_minimum_required( VERSION 2.8 )

project( CovariantVectorNorm )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CovariantVectorNorm CovariantVectorNorm.cxx )
target_link_libraries( CovariantVectorNorm ${ITK_LIBRARIES} )

install( TARGETS CovariantVectorNorm
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES CovariantVectorNorm.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CovariantVectorNorm
  COMPONENT Code
)

enable_testing()
add_test( NAME CovariantVectorNormTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CovariantVectorNorm )

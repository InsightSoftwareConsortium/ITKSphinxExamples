cmake_minimum_required( VERSION 2.8 )

project( CovariantVector )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( CovariantVector CovariantVector.cxx )
target_link_libraries( CovariantVector ${ITK_LIBRARIES} )

install( TARGETS CovariantVector
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES CovariantVector.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CovariantVector
  COMPONENT Code
)

enable_testing()
add_test( NAME CovariantVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CovariantVector )

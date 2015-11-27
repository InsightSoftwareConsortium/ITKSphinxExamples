cmake_minimum_required( VERSION 2.8.6 )

project( AddOffsetToIndex )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( AddOffsetToIndex Code.cxx Code.py )
target_link_libraries( AddOffsetToIndex ${ITK_LIBRARIES} )

install( TARGETS AddOffsetToIndex
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/AddOffsetToIndex
  COMPONENT Code
)

enable_testing()
add_test( NAME AddOffsetToIndexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddOffsetToIndex )

if( ITK_WRAP_PYTHON )
  add_test( NAME AddOffsetToIndexTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
  )
  set_property( GLOBAL PROPERTY AddOffsetToIndexTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY AddOffsetToIndexTestHASPYTHONTEST FALSE )
endif()

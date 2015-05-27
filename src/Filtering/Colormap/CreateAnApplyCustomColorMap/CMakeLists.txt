cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/sf4.png )
set( output_image Output.png )
set( test_options )

project( CreateAnApplyCustomColorMap )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAnApplyCustomColorMap Code.cxx )
target_link_libraries( CreateAnApplyCustomColorMap ${ITK_LIBRARIES} )

install( TARGETS CreateAnApplyCustomColorMap
  DESTINATION bin/ITKExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/Colormap/CreateAnApplyCustomColorMap
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAnApplyCustomColorMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnApplyCustomColorMap
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME CreateAnApplyCustomColorMapTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY CreateAnApplyCustomColorMapTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY CreateAnApplyCustomColorMapTestHASPYTHONTEST FALSE )
endif()

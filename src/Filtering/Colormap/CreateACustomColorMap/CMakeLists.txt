cmake_minimum_required(VERSION 3.10.2)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/sf4.png )
set( output_image Output.png )
set( test_options )

project( CreateACustomColorMap )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateACustomColorMap Code.cxx )
target_link_libraries( CreateACustomColorMap ${ITK_LIBRARIES} )

install( TARGETS CreateACustomColorMap
  DESTINATION bin/ITKExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/Colormap/CreateACustomColorMap
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateACustomColorMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateACustomColorMap
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME CreateACustomColorMapTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

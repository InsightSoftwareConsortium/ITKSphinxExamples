cmake_minimum_required(VERSION 3.10.2)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image Output.png )
set( test_options )

project( ApplyAColorMapToAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAColorMapToAnImage Code.cxx )
target_link_libraries( ApplyAColorMapToAnImage ${ITK_LIBRARIES} )

install( TARGETS ApplyAColorMapToAnImage
  DESTINATION bin/ITKExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/Colormap/ApplyAColorMapToAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAColorMapToAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAColorMapToAnImage
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ApplyAColorMapToAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

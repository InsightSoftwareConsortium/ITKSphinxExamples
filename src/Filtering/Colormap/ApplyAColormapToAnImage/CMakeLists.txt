cmake_minimum_required(VERSION 3.10.2)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png )
set( output_image Output.png )
set( test_options )

project( ApplyAColormapToAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAColormapToAnImage Code.cxx )
target_link_libraries( ApplyAColormapToAnImage ${ITK_LIBRARIES} )

install( TARGETS ApplyAColormapToAnImage
  DESTINATION bin/ITKSphinxExamples/Filtering/Colormap
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Colormap/ApplyAColormapToAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyAColormapToAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAColormapToAnImage
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ApplyAColormapToAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

cmake_minimum_required(VERSION 3.8.2)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png )
set( output_image Output.png )

project( RemoveHolesNotConnectedToImageBoundaries )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( RemoveHolesNotConnectedToImageBoundaries Code.cxx )
target_link_libraries( RemoveHolesNotConnectedToImageBoundaries ${ITK_LIBRARIES} )

install( TARGETS RemoveHolesNotConnectedToImageBoundaries
  DESTINATION bin/ITKExamples/Filtering/LabelMap/
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/RemoveHolesNotConnectedToImageBoundaries
  COMPONENT Code
  )

enable_testing()
add_test( NAME RemoveHolesNotConnectedToImageBoundariesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RemoveHolesNotConnectedToImageBoundaries
  ${input_image}
  ${output_image}
)

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME RemoveHolesNotConnectedToImageBoundariesTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()

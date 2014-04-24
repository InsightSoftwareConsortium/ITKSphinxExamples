cmake_minimum_required( VERSION 2.8.6 )

set( example_name ErodeABinaryImage )
set( folder Filtering/BinaryMathematicalMorphology/ )
set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png )
set( output_image Output.png )
set( test_options 3 )

project( ${example_name} )

find_package( ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( ${example_name} Code.cxx )
target_link_libraries( ${example_name} ${ITK_LIBRARIES} )

install( TARGETS ${example_name}
  DESTINATION bin/ITKExamples/${folder}
  COMPONENT Runtime
)

set( python_file )
if(EXISTS Code.py )
  set( ${python_file} Code.py )
endif()

install( FILES Code.cxx CMakeLists.txt ${python_file}
  DESTINATION share/ITKExamples/Code/${folder}/${example_name}
  COMPONENT Code
)

enable_testing()

add_test( NAME ${example_name}Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${example_name}
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ${ITK_WRAP_PYTHON} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ${example_name}TestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY ${example_name}TestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ${example_name}TestHASPYTHONTEST FALSE )
endif()

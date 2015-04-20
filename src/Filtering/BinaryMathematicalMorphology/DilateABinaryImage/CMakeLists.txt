cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png )
set( output_image Output.png )
set( test_options 3 )

project( DilateABinaryImage )

find_package( ITK REQUIRED
  COMPONENTS
  ITKBinaryMathematicalMorphology
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( DilateABinaryImage Code.cxx )
target_link_libraries( DilateABinaryImage ${ITK_LIBRARIES} )

install( TARGETS DilateABinaryImage
  DESTINATION bin/ITKExamples/Filtering/BinaryMathematicalMorphology/
  COMPONENT Runtime
)

set( python_file )
if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  set( python_file Code.py )
endif()

install( FILES Code.cxx CMakeLists.txt ${python_file}
  DESTINATION share/ITKExamples/Code/Filtering/BinaryMathematicalMorphology/DilateABinaryImage
  COMPONENT Code
)

enable_testing()

add_test( NAME DilateABinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DilateABinaryImage
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME DilateABinaryImageTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY DilateABinaryImageTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY DilateABinaryImageTestHASPYTHONTEST FALSE )
endif()

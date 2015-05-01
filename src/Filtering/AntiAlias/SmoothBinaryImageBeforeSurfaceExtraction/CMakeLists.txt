cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/VentricleModel.png )
set( output_image Output.mha )
set( test_options 0.001 50 2 )

project( SmoothBinaryImageBeforeSurfaceExtraction )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SmoothBinaryImageBeforeSurfaceExtraction Code.cxx )
target_link_libraries( SmoothBinaryImageBeforeSurfaceExtraction ${ITK_LIBRARIES} )

install( TARGETS SmoothBinaryImageBeforeSurfaceExtraction
  DESTINATION bin/ITKExamples/Filtering/AntiAlias
  COMPONENT Runtime
)

set( python_file )
if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  set( python_file Code.py )
endif()

install( FILES Code.cxx CMakeLists.txt ${python_file}
  DESTINATION share/ITKExamples/Code/Filtering/AntiAlias/SmoothBinaryImageBeforeSurfaceExtraction
  COMPONENT Code
)

enable_testing()
add_test( NAME SmoothBinaryImageBeforeSurfaceExtractionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothBinaryImageBeforeSurfaceExtraction
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME SmoothBinaryImageBeforeSurfaceExtractionTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    ${test_options}
  )
  set_property( GLOBAL PROPERTY SmoothBinaryImageBeforeSurfaceExtractionTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY SmoothBinaryImageBeforeSurfaceExtractionTestHASPYTHONTEST FALSE )
endif()

cmake_minimum_required( VERSION 2.8.6 )

set( example_name GenerateSlicesFromVolume )
set( folder IO/ImageBase/ )
set( input_image ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha )
set( output_image Output )

project( GenerateSlicesFromVolume )

find_package( ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKImageIntensity
  ITKIOPNG
  ITKIOMeta
  )
include( ${ITK_USE_FILE} )

add_executable( ${example_name} Code.cxx )
target_link_libraries( ${example_name} ${ITK_LIBRARIES} )

install( TARGETS ${example_name}
  DESTINATION bin/ITKExamples/${folder}
  COMPONENT Runtime
  )

set( python_file )
if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  set( python_file Code.py )
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
)

if( ITK_WRAP_PYTHON AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  add_test( NAME ${example_name}TestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
    "Python.png"
  )
  set_property( GLOBAL PROPERTY ${example_name}TestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ${example_name}TestHASPYTHONTEST FALSE )
endif()

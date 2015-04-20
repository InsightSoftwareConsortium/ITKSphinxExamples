cmake_minimum_required( VERSION 2.8.6 )

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/VisibleWomanHeadSlice.png )
set( output_image Output.png )

project( ResampleAVectorImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ResampleAVectorImage Code.cxx )
target_link_libraries( ResampleAVectorImage ${ITK_LIBRARIES} )

install( TARGETS ResampleAVectorImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid/
  COMPONENT Runtime
)

set( python_file )
if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  set( python_file Code.py )
endif()

install( FILES Code.cxx CMakeLists.txt ${python_file}
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/ResampleAVectorImage
  COMPONENT Code
)

enable_testing()

add_test( NAME ResampleAVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleAVectorImage
  ${input_image}
  ${output_image}
)

if( ITK_WRAP_PYTHON AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Code.py )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ResampleAVectorImageTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    ${output_image}
  )
  set_property( GLOBAL PROPERTY ResampleAVectorImageTestHASPYTHONTEST TRUE )
elseif()
  set_property( GLOBAL PROPERTY ResampleAVectorImageTestHASPYTHONTEST FALSE )
endif()

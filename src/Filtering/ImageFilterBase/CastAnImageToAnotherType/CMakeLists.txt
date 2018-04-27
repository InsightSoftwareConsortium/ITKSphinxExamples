cmake_minimum_required(VERSION 3.10.2)

project( CastAnImageToAnotherType )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CastAnImageToAnotherType Code.cxx )
target_link_libraries( CastAnImageToAnotherType ${ITK_LIBRARIES} )

install( TARGETS CastAnImageToAnotherType
  DESTINATION bin/ITKExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFilterBase/CastAnImageToAnotherType
  COMPONENT Code
)

enable_testing()
add_test( NAME CastAnImageToAnotherTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CastAnImageToAnotherType
    ${CMAKE_CURRENT_BINARY_DIR}/CorpusCallosumMeanShape.mha
    Output.png
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME CastAnImageToAnotherTypeTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/CorpusCallosumMeanShape.mha
      OutputPython.png
    )
endif()

cmake_minimum_required( VERSION 2.8 )

project( CastAnImageToAnotherType )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CastAnImageToAnotherType CastAnImageToAnotherType.cxx )
target_link_libraries( CastAnImageToAnotherType ${ITK_LIBRARIES} )

install( TARGETS CastAnImageToAnotherType
  DESTINATION bin/ITKExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
)

install( FILES CastAnImageToAnotherType.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFilterBase/CastAnImageToAnotherType
  COMPONENT Code
)

enable_testing()
add_test( NAME CastAnImageToAnotherTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CastAnImageToAnotherType
    ${CMAKE_CURRENT_BINARY_DIR}/CorpusCallosumMeanShape.mha
    CastAnImageToAnotherTypeOutput.png
)

cmake_minimum_required(VERSION 3.16.3)

project( DilateUsingFunctionalGrayscale )

find_package( ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( DilateUsingFunctionalGrayscale Code.cxx )
target_link_libraries( DilateUsingFunctionalGrayscale ${ITK_LIBRARIES} )

install( TARGETS DilateUsingFunctionalGrayscale
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/DilateUsingFunctionalGrayscale
  COMPONENT Code
)

enable_testing()
add_test( NAME DilateUsingFunctionalGrayscaleTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DilateUsingFunctionalGrayscale
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    5
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME DilateUsingFunctionalGrayscaleTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      5
    )
endif()

cmake_minimum_required( VERSION 2.8.6 )

project( ErodeAGrayscaleImage )

find_package( ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include( ${ITK_USE_FILE} )

add_executable( ErodeAGrayscaleImage Code.cxx )
target_link_libraries( ErodeAGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ErodeAGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/MathematicalMorphology/ErodeAGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ErodeAGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ErodeAGrayscaleImage
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    5
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME ErodeAGrayscaleImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      5
    )
endif()

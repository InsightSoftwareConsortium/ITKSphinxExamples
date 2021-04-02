cmake_minimum_required(VERSION 3.10.2)

project( CalculateImageMoments )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CalculateImageMoments Code.cxx )
target_link_libraries( CalculateImageMoments ${ITK_LIBRARIES} )

install( TARGETS CalculateImageMoments
  DESTINATION bin/ITKExamples/Filtering/ImageStatistics
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Filtering/ImageStatistics/CalculateImageMoments
  COMPONENT Code
)

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/ellipse.mha)

add_test( NAME CalculateImageMomentsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CalculateImageMoments
  ${input_image}
)

if( ITK_WRAP_PYTHON )
  find_package(PythonInterp REQUIRED)
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME CalculateImageMomentsTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
    )
endif()

cmake_minimum_required(VERSION 3.8.2)

project( ApplyMeanFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyMeanFilter Code.cxx )
target_link_libraries( ApplyMeanFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyMeanFilter
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/ApplyMeanFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME ApplyMeanFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyMeanFilter
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    2
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME ApplyMeanFilterTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      2
    )
endif()

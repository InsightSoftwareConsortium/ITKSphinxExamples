cmake_minimum_required( VERSION 2.8.6 )

project( SmoothWithRecursiveGaussian )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SmoothWithRecursiveGaussian Code.cxx )
target_link_libraries( SmoothWithRecursiveGaussian ${ITK_LIBRARIES} )

install( TARGETS SmoothWithRecursiveGaussian
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/SmoothWithRecursiveGaussian
  COMPONENT Code
)

enable_testing()
add_test( NAME SmoothWithRecursiveGaussianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothWithRecursiveGaussian
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    3
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME SmoothWithRecursiveGaussianTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      OutputPython.png
      3
    )
endif()

cmake_minimum_required(VERSION 3.10.2)

project( ResampleAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ResampleAnImage Code.cxx )
target_link_libraries( ResampleAnImage ${ITK_LIBRARIES} )

install( TARGETS ResampleAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/ResampleAnImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ResampleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    2
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME ResampleAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      OutputPython.png
      2
    )
endif()

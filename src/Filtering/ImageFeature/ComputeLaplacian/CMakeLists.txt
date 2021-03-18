cmake_minimum_required(VERSION 3.10.2)

project( ComputeLaplacian )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeLaplacian Code.cxx )
target_link_libraries( ComputeLaplacian ${ITK_LIBRARIES} )

install( TARGETS ComputeLaplacian
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/ComputeLaplacian
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeLaplacianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeLaplacian
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME ComputeLaplacianTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
    )
endif()

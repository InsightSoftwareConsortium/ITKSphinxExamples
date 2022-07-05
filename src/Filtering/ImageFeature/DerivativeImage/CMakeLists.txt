cmake_minimum_required(VERSION 3.16.3)

project( DerivativeImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DerivativeImage Code.cxx )
target_link_libraries( DerivativeImage ${ITK_LIBRARIES} )

install( TARGETS DerivativeImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/DerivativeImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME DerivativeImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DerivativeImage
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.mha Output_normalized.mha 1 1
  )

#if( ITK_WRAP_PYTHON )
#  add_test( NAME DerivativeImageTestPython
#    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
#      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
#      OutputPython.png
#    )
#endif()

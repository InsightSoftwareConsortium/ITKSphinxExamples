cmake_minimum_required( VERSION 2.8.6 )

project( ComputeSigmoid )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeSigmoid Code.cxx )
target_link_libraries( ComputeSigmoid ${ITK_LIBRARIES} )

install( TARGETS ComputeSigmoid
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ComputeSigmoid
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputeSigmoidTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeSigmoid
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output.png
    10 240 10 170)

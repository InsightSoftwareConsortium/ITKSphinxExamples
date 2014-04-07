cmake_minimum_required( VERSION 2.8.5 )

project( ComputePeronaMalikAnisotropicDiffusion )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ComputePeronaMalikAnisotropicDiffusion Code.cxx )
target_link_libraries( ComputePeronaMalikAnisotropicDiffusion ${ITK_LIBRARIES} )

install( TARGETS ComputePeronaMalikAnisotropicDiffusion
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/ComputePeronaMalikAnisotropicDiffusion
  COMPONENT Code
  )

enable_testing()
add_test( NAME ComputePeronaMalikAnisotropicDiffusionTest
  COMMAND
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputePeronaMalikAnisotropicDiffusion
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  ComputePeronaMalikAnisotropicDiffusionTest.mha
  5
  2.0
  )

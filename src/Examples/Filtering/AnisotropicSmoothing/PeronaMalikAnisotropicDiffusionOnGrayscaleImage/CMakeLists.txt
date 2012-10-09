cmake_minimum_required( VERSION 2.8 )

project( PeronaMalikAnisotropicDiffusionOnGrayscaleImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( PeronaMalikAnisotropicDiffusionOnGrayscaleImage PeronaMalikAnisotropicDiffusionOnGrayscaleImage.cxx )
target_link_libraries( PeronaMalikAnisotropicDiffusionOnGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS PeronaMalikAnisotropicDiffusionOnGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/AnisotropicSmoothing
  COMPONENT Runtime
  )

install( FILES PeronaMalikAnisotropicDiffusionOnGrayscaleImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/AnisotropicSmoothing/PeronaMalikAnisotropicDiffusionOnGrayscaleImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME PeronaMalikAnisotropicDiffusionOnGrayscaleImageTest
  COMMAND
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PeronaMalikAnisotropicDiffusionOnGrayscaleImage
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  PeronaMalikAnisotropicDiffusionOnGrayscaleImageTest.mha
  5
  1.0
  )

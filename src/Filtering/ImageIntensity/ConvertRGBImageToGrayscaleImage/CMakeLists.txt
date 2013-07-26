cmake_minimum_required( VERSION 2.8 )

project( ConvertRGBImageToGrayscaleImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ConvertRGBImageToGrayscaleImage Code.cxx )
target_link_libraries( ConvertRGBImageToGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ConvertRGBImageToGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ConvertRGBImageToGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ConvertRGBImageToGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertRGBImageToGrayscaleImage
    ${CMAKE_CURRENT_BINARY_DIR}/itk_eg_logo.png
    Output.png
)

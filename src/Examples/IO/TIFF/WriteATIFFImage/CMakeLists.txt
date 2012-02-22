cmake_minimum_required( VERSION 2.8 )

project( WriteATIFFImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( WriteATIFFImage WriteATIFFImage.cxx )
target_link_libraries( WriteATIFFImage ${ITK_LIBRARIES} )

install( TARGETS WriteATIFFImage
  DESTINATION bin/ITKExamples/IO/TIFF/
  COMPONENT Runtime
)

install( FILES WriteATIFFImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/TIFF/WriteATIFFImage
  COMPONENT Code
)

enable_testing()
add_test( NAME WriteATIFFImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WriteATIFFImage
    ${CMAKE_CURRENT_BINARY_DIR}/WriteATIFFImageOutput.tif )

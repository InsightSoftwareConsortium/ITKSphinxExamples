cmake_minimum_required( VERSION 2.8 )

project( DilateABinaryImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DilateABinaryImage DilateABinaryImage.cxx )
target_link_libraries( DilateABinaryImage ${ITK_LIBRARIES} )

enable_testing()
add_test( DilateABinaryImageTest DilateABinaryImage
  ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png DilateABinaryImageOutput.png 3
  )

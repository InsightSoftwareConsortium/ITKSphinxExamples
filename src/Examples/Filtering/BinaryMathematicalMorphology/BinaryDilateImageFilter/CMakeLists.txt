cmake_minimum_required( VERSION 2.8 )

project( BinaryDilateImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( BinaryDilateImageFilter BinaryDilateImageFilter.cxx )
target_link_libraries( BinaryDilateImageFilter ${ITK_LIBRARIES} )

enable_testing()
add_test( BinaryDilateImageFilterTest BinaryDilateImageFilter )

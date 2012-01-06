cmake_minimum_required( VERSION 2.8 )

project( BinaryDilateImageFilter )

find_package( ItkVtkGlue REQUIRED )

include( ${ItkVtkGlue_USE_FILE} )

add_executable( BinaryDilateImageFilter BinaryDilateImageFilter.cxx )

target_link_libraries( BinaryDilateImageFilter ItkVtkGlue ${VTK_LIBRARIES}
  ${ITK_LIBRARIES} )

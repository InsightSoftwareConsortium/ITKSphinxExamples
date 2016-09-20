cmake_minimum_required( VERSION 2.8.6 )
project( ReadDICOMSeriesAndWrite3DImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReadDICOMSeriesAndWrite3DImage Code.cxx )
target_link_libraries( ReadDICOMSeriesAndWrite3DImage ${ITK_LIBRARIES} )

install( TARGETS ReadDICOMSeriesAndWrite3DImage
  DESTINATION bin/ITKExamples/IO/GDCM
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/GDCM/ReadDICOMSeriesAndWrite3DImage
  COMPONENT Code
  )

# we need images for testing
# enable_testing()
# add_test( NAME ReadDICOMSeriesAndWrite3DImage
#   COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadDICOMSeriesAndWrite3DImage )

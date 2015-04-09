cmake_minimum_required( VERSION 2.8.6 )
project( DicomSeriesReadImageWrite3 )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DicomSeriesReadImageWrite3 Code.cxx )
target_link_libraries( DicomSeriesReadImageWrite3 ${ITK_LIBRARIES} )

install( TARGETS DicomSeriesReadImageWrite3
  DESTINATION bin/ITKExamples/IO/DICOM
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/DICOM/DicomSeriesReadImageWrite3
  COMPONENT Code
  )

# we need images for testing
# enable_testing()
# add_test( NAME DicomSeriesReadImageWrite3Test
#   COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DicomSeriesReadImageWrite3 )

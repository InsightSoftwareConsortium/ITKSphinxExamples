cmake_minimum_required(VERSION 3.8.2)
project( ReadDICOMSeriesAndWrite3DImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReadDICOMSeriesAndWrite3DImage Code.cxx )
target_link_libraries( ReadDICOMSeriesAndWrite3DImage ${ITK_LIBRARIES} )

install( TARGETS ReadDICOMSeriesAndWrite3DImage
  DESTINATION bin/ITKExamples/IO/GDCM
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/IO/GDCM/ReadDICOMSeriesAndWrite3DImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ReadDICOMSeriesAndWrite3DImage
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadDICOMSeriesAndWrite3DImage
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}/Image3D.nrrd"
    )

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME ReadDICOMSeriesAndWrite3DImagePython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      "${CMAKE_CURRENT_BINARY_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}/Image3D.Python.nrrd"
    )
endif()

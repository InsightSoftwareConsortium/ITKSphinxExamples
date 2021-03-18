cmake_minimum_required(VERSION 3.10.2)

project( ProcessImageChunks )

find_package( ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKSmoothing
  ITKIOPNG
  ITKIOMeta
  )
include( ${ITK_USE_FILE} )

add_executable( ProcessImageChunks Code.cxx )
target_link_libraries( ProcessImageChunks ${ITK_LIBRARIES} )

install( TARGETS ProcessImageChunks
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase/
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ProcessImageChunks
  COMPONENT Code
)

enable_testing()

add_test( NAME ProcessImageChunksTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ProcessImageChunks
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.mha
)

if( ITK_WRAP_PYTHON )
  add_test( NAME ProcessImageChunksTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    OutputPython.mha
    )
endif()

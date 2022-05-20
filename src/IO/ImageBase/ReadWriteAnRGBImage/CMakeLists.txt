cmake_minimum_required(VERSION 3.16.3)

project( ReadWriteAnRGBImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReadWriteAnRGBImage Code.cxx )
target_link_libraries( ReadWriteAnRGBImage ${ITK_LIBRARIES} )

install( TARGETS ReadWriteAnRGBImage
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase/
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ReadWriteAnRGBImage
  COMPONENT Code
)

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/peppers.png )
set( output_image Output.png )

enable_testing()
add_test( NAME ReadWriteAnRGBImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadWriteAnRGBImage
    ${input_image}
    ${output_image}
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ReadWriteAnRGBImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()

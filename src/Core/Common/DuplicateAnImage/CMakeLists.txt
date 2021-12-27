cmake_minimum_required(VERSION 3.16.3)

project( DuplicateAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DuplicateAnImage Code.cxx )
target_link_libraries( DuplicateAnImage ${ITK_LIBRARIES} )

install( TARGETS DuplicateAnImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/DuplicateAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME DuplicateAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DuplicateAnImage )

if( ITK_WRAP_PYTHON )
  add_test( NAME DuplicateAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

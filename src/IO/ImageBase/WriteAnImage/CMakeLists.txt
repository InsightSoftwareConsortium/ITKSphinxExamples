cmake_minimum_required(VERSION 3.16.3)

project( WriteAnImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( WriteAnImage Code.cxx )
target_link_libraries( WriteAnImage ${ITK_LIBRARIES} )

install( TARGETS WriteAnImage
  DESTINATION bin/ITKSphinxExamples/Base/
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Base//WriteAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME WriteAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WriteAnImage )

if(ITK_WRAP_PYTHON)
  add_test(NAME WriteAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

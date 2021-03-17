cmake_minimum_required(VERSION 3.10.2)

project( CreateAVector )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAVector Code.py Code.cxx )
target_link_libraries( CreateAVector ${ITK_LIBRARIES} )

install( TARGETS CreateAVector
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAVector
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAVector )

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAVectorTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

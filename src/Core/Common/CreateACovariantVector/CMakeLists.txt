cmake_minimum_required(VERSION 3.10.2)

project( CreateACovariantVector )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateACovariantVector Code.cxx Code.py)
target_link_libraries( CreateACovariantVector ${ITK_LIBRARIES} )

install( TARGETS CreateACovariantVector
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateACovariantVector
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateACovariantVectorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateACovariantVector )

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateACovariantVectorTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

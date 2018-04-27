cmake_minimum_required(VERSION 3.10.2)

project( CreateAIndex )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAIndex Code.py Code.cxx )
target_link_libraries( CreateAIndex ${ITK_LIBRARIES} )

install( TARGETS CreateAIndex
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAIndex
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAIndexTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAIndex )

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAIndexTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

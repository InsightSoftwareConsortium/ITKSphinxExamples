cmake_minimum_required(VERSION 3.10.2)

project( CreateAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAPointSet Code.py Code.cxx )
target_link_libraries( CreateAPointSet ${ITK_LIBRARIES} )

install( TARGETS CreateAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAPointSet
)

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAPointSetTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

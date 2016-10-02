cmake_minimum_required( VERSION 2.8.6 )

project( CreateASize )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateASize Code.py Code.cxx )
target_link_libraries( CreateASize ${ITK_LIBRARIES} )

install( TARGETS CreateASize
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateASize
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateASizeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateASize )

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateASizeTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

cmake_minimum_required(VERSION 3.10.2)

project( CreateAFixedArray )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAFixedArray Code.cxx Code.py )
target_link_libraries( CreateAFixedArray ${ITK_LIBRARIES} )

install( TARGETS CreateAFixedArray
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAFixedArray
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAFixedArrayTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAFixedArray )

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAFixedArrayTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

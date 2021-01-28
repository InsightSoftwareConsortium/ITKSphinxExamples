cmake_minimum_required(VERSION 3.10.2)

project( VectorDotProduct )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( VectorDotProduct Code.cxx Code.py)
target_link_libraries( VectorDotProduct ${ITK_LIBRARIES} )

install( TARGETS VectorDotProduct
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/VectorDotProduct
  COMPONENT Code
)

enable_testing()
add_test( NAME VectorDotProductTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VectorDotProduct )

if( ITK_WRAP_PYTHON )
  add_test( NAME VectorDotProductTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

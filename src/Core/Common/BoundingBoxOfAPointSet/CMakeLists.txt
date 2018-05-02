cmake_minimum_required(VERSION 3.10.2)

project( BoundingBoxOfAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( BoundingBoxOfAPointSet Code.cxx Code.py )
target_link_libraries( BoundingBoxOfAPointSet ${ITK_LIBRARIES} )

install( TARGETS BoundingBoxOfAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/BoundingBoxOfAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME BoundingBoxOfAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BoundingBoxOfAPointSet )

if(ITK_WRAP_PYTHON)
  add_test(NAME BoundingBoxOfAPointSetTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

cmake_minimum_required(VERSION 3.10.2)

project( IsPixelInsideRegion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( IsPixelInsideRegion Code.cxx )
target_link_libraries( IsPixelInsideRegion ${ITK_LIBRARIES} )

install( TARGETS IsPixelInsideRegion
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/IsPixelInsideRegion
  COMPONENT Code
)

enable_testing()
add_test( NAME IsPixelInsideRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IsPixelInsideRegion )

if(ITK_WRAP_PYTHON)
  add_test(NAME IsPixelInsideRegionPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

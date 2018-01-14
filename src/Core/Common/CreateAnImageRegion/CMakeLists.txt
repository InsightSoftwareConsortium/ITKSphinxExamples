cmake_minimum_required(VERSION 3.8.2)

project( CreateAnImageRegion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAnImageRegion Code.cxx Code.py )
target_link_libraries( CreateAnImageRegion ${ITK_LIBRARIES} )

install( TARGETS CreateAnImageRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAnImageRegion
  COMPONENT Code
)

enable_testing()
set(testOutputRegex "ImageRegion")
add_test( NAME CreateAnImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnImageRegion )
set_tests_properties(CreateAnImageRegionTest PROPERTIES
    PASS_REGULAR_EXPRESSION "${testOutputRegex}")

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAnImageRegionTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
  set_tests_properties(CreateAnImageRegionTestPython PROPERTIES
      PASS_REGULAR_EXPRESSION "${testOutputRegex}")
endif()

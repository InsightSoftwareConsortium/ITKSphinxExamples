cmake_minimum_required( VERSION 2.8.6 )

project( CreateAImageRegion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateAImageRegion Code.cxx Code.py )
target_link_libraries( CreateAImageRegion ${ITK_LIBRARIES} )

install( TARGETS CreateAImageRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAImageRegion
  COMPONENT Code
)

enable_testing()
set(testOutputRegex "^  RTTI typeinfo:   itk::Image<unsigned char, 3u>")
add_test( NAME CreateAImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAImageRegion )
set_tests_properties(CreateAImageRegionTest PROPERTIES
    PASS_REGULAR_EXPRESSION "${testOutputRegex}")

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAImageRegionTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
  set_tests_properties(CreateAImageRegionTestPython PROPERTIES
      PASS_REGULAR_EXPRESSION "${testOutputRegex}")
endif()

cmake_minimum_required(VERSION 3.16.3)

project(CreateAnImageRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx Code.py)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAnImageRegion
  COMPONENT Code
)

enable_testing()
set(testOutputRegex "ImageRegion")
add_test(NAME CreateAnImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
set_tests_properties(CreateAnImageRegionTest PROPERTIES
    PASS_REGULAR_EXPRESSION "${testOutputRegex}")

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAnImageRegionTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
  set_tests_properties(CreateAnImageRegionTestPython PROPERTIES
      PASS_REGULAR_EXPRESSION "${testOutputRegex}")
endif()

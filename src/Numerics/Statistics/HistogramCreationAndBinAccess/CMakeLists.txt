cmake_minimum_required(VERSION 3.16.3)

project(HistogramCreationAndBinAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Statistics/HistogramCreationAndBinAccess/
  COMPONENT Code
  )


enable_testing()

set(HistogramCreationAndBinAccessTest_Regex "Frequency of the bin at index \\[0, 2\\] is 5 and the bin's instance identifier is 6")

add_test(NAME HistogramCreationAndBinAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  )
set_tests_properties(HistogramCreationAndBinAccessTest PROPERTIES
  PASS_REGULAR_EXPRESSION "${HistogramCreationAndBinAccessTest_Regex}")

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME HistogramCreationAndBinAccessTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
  set_tests_properties(HistogramCreationAndBinAccessTestPython PROPERTIES
    PASS_REGULAR_EXPRESSION "${HistogramCreationAndBinAccessTest_Regex}")
endif()

cmake_minimum_required(VERSION 3.10.2)

project(HistogramCreationAndBinAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(HistogramCreationAndBinAccess Code.cxx)
target_link_libraries(HistogramCreationAndBinAccess ${ITK_LIBRARIES})

install(TARGETS HistogramCreationAndBinAccess
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/HistogramCreationAndBinAccess/
  COMPONENT Code
  )


enable_testing()

set(HistogramCreationAndBinAccessTest_Regex "^Frequency of the bin at index \\[0, 2\\] is 5 and the bin's instance identifier is 6")

add_test(NAME HistogramCreationAndBinAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/HistogramCreationAndBinAccess
  )
set_tests_properties(HistogramCreationAndBinAccessTest PROPERTIES
  PASS_REGULAR_EXPRESSION "${HistogramCreationAndBinAccessTest_Regex}")

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME HistogramCreationAndBinAccessTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
  set_tests_properties(HistogramCreationAndBinAccessTestPython PROPERTIES
    PASS_REGULAR_EXPRESSION "${HistogramCreationAndBinAccessTest_Regex}")
endif()

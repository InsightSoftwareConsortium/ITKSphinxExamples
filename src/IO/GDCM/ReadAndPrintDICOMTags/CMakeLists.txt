cmake_minimum_required(VERSION 3.16.3)

project(ReadAndPrintDICOMTags)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/GDCM
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/IO/GDCM/ReadAndPrintDICOMTags
  COMPONENT Code
)

enable_testing()
add_test(NAME ReadAndPrintDICOMTagsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  "${CMAKE_CURRENT_BINARY_DIR}"
)

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ReadAndPrintDICOMTagsTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

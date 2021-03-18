cmake_minimum_required(VERSION 3.10.2)

project(SetDefaultNumberOfThreads)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(SetDefaultNumberOfThreads Code.cxx)
target_link_libraries(SetDefaultNumberOfThreads ${ITK_LIBRARIES})

install(TARGETS SetDefaultNumberOfThreads
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/SetDefaultNumberOfThreads
  COMPONENT Code
)

enable_testing()

set(test_options 3)

add_test(NAME SetDefaultNumberOfThreadsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SetDefaultNumberOfThreads
  ${test_options}
)

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  add_test( NAME SetDefaultNumberOfThreadsTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${test_options}
    )
endif()

cmake_minimum_required(VERSION 3.10.2)

project(AccessDataInCells)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(AccessDataInCells Code.cxx)
target_link_libraries(AccessDataInCells ${ITK_LIBRARIES})

install(TARGETS AccessDataInCells
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/AccessDataInCells/
  COMPONENT Code
  )

enable_testing()

add_test(NAME AccessDataInCellsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AccessDataInCells)

if(ITK_WRAP_PYTHON)
  add_test(NAME AccessDataInCellsTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

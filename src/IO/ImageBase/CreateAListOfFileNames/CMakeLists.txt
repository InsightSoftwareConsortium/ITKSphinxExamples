cmake_minimum_required(VERSION 3.16.3)

project(CreateAListOfFileNames)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(CreateAListOfFileNames Code.cxx)
target_link_libraries(CreateAListOfFileNames ${ITK_LIBRARIES})

install(TARGETS CreateAListOfFileNames
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/CreateAListOfFileNames
  COMPONENT Code
)

enable_testing()
add_test(NAME CreateAListOfFileNamesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAListOfFileNames)

if(ITK_WRAP_PYTHON)
add_test(NAME CreateAListOfFileNamesTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

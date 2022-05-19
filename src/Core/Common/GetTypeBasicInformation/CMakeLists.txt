cmake_minimum_required(VERSION 3.16.3)

project(GetTypeBasicInformation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(GetTypeBasicInformation Code.cxx)
target_link_libraries(GetTypeBasicInformation ${ITK_LIBRARIES})

install(TARGETS GetTypeBasicInformation
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/GetTypeBasicInformation
  COMPONENT Code
)

enable_testing()
add_test(NAME GetTypeBasicInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetTypeBasicInformation)

if(ITK_WRAP_PYTHON)
  add_test(NAME GetTypeBasicInformationTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

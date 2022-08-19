cmake_minimum_required(VERSION 3.16.3)

project(EagerModuleLoadingPython)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

install(FILES Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/EagerModuleLoadingPython/
  COMPONENT Code
  )

enable_testing()
if(ITK_WRAP_PYTHON)
  add_test(NAME EagerModuleLoadingPythonTest
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()
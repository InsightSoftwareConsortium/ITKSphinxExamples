cmake_minimum_required(VERSION 3.16.3)

project( ConvertNumPyArrayToitkImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

if(ITK_WRAP_PYTHON)
  add_test(NAME  ConvertNumPyArrayToitkImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

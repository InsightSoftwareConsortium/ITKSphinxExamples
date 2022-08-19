cmake_minimum_required(VERSION 3.16.3)

project( ConvertNumPyArrayToitkImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Slicer.png)

if(ITK_WRAP_PYTHON)
  add_test(NAME  ConvertNumPyArrayToitkImageTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image}
    SliceRevised.png
    )
endif()

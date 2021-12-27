cmake_minimum_required(VERSION 3.16.3)

project(CreateSobelKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateSobelKernel Code.cxx)
target_link_libraries(CreateSobelKernel ${ITK_LIBRARIES})

install(TARGETS CreateSobelKernel
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateSobelKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateSobelKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateSobelKernel)

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateSobelKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()


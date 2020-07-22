cmake_minimum_required(VERSION 3.10.2)

project(CreateForwardDifferenceKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateForwardDifferenceKernel Code.cxx)
target_link_libraries(CreateForwardDifferenceKernel ${ITK_LIBRARIES})

install(TARGETS CreateForwardDifferenceKernel
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateForwardDifferenceKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateForwardDifferenceKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateForwardDifferenceKernel)

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateForwardDifferenceKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

cmake_minimum_required(VERSION 3.16.3)

project(CreateLaplacianKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateLaplacianKernel Code.cxx)
target_link_libraries(CreateLaplacianKernel ${ITK_LIBRARIES})

install(TARGETS CreateLaplacianKernel
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateLaplacianKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateLaplacianKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateLaplacianKernel)

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateLaplacianKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

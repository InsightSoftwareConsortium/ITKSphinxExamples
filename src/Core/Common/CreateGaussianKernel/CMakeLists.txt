cmake_minimum_required(VERSION 3.10.2)

project(CreateGaussianKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateGaussianKernel Code.cxx)
target_link_libraries(CreateGaussianKernel ${ITK_LIBRARIES})

install(TARGETS CreateGaussianKernel
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateGaussianKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateGaussianKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateGaussianKernel)

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateGaussianKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

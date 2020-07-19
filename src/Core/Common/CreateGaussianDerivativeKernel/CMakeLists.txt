cmake_minimum_required(VERSION 3.10.2)

project(CreateGaussianDerivativeKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateGaussianDerivativeKernel Code.cxx)
target_link_libraries(CreateGaussianDerivativeKernel ${ITK_LIBRARIES})

install(TARGETS CreateGaussianDerivativeKernel
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateGaussianDerivativeKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateGaussianDerivativeKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateGaussianDerivativeKernel)

if( ITK_WRAP_PYTHON )
  add_test( NAME CreateGaussianDerivativeKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

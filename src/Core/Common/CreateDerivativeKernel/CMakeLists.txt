cmake_minimum_required(VERSION 3.16.3)

project(CreateDerivativeKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateDerivativeKernel Code.cxx)
target_link_libraries(CreateDerivativeKernel ${ITK_LIBRARIES})

install(TARGETS CreateDerivativeKernel
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateDerivativeKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateDerivativeKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateDerivativeKernel)

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateDerivativeKernelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

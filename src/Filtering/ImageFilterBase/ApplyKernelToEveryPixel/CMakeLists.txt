cmake_minimum_required(VERSION 3.16.3)

project(ApplyKernelToEveryPixel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ApplyKernelToEveryPixel Code.cxx)
target_link_libraries(ApplyKernelToEveryPixel ${ITK_LIBRARIES})

install(TARGETS ApplyKernelToEveryPixel
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFilterBase/ApplyKernelToEveryPixel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ApplyKernelToEveryPixelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyKernelToEveryPixel)

if(ITK_WRAP_PYTHON)
  add_test(NAME ApplyKernelToEveryPixelTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

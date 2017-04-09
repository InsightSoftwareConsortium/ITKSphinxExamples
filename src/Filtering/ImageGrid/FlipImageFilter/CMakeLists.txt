cmake_minimum_required(VERSION 2.8.9)

project(FlipImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FlipImageFilter Code.cxx)
target_link_libraries(FlipImageFilter ${ITK_LIBRARIES})

install(TARGETS FlipImageFilter
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Core/Common/FlipImageFilter/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png)
set(output_image Output.png)
set(flipaxisx 1)
set(flipaxisy -1)

add_test(NAME FlipImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FlipImageFilter
    ${input_image}
    ${output_image}
    ${flipaxisx}
    ${flipaxisy}
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME FlipImageFilterTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${flipaxisx}
      ${flipaxisy}
    )
endif()

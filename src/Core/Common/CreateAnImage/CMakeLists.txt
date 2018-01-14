cmake_minimum_required(VERSION 3.8.2)

project(CreateAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateAnImage Code.cxx)
target_link_libraries(CreateAnImage ${ITK_LIBRARIES})

install(TARGETS CreateAnImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAnImage/
  COMPONENT Code
  )


enable_testing()

add_test(NAME CreateAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnImage
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  add_test(NAME CreateAnImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

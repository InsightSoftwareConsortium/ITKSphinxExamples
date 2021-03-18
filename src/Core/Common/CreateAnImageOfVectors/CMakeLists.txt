cmake_minimum_required(VERSION 3.10.2)

project(CreateAnImageOfVectors)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateAnImageOfVectors Code.cxx)
target_link_libraries(CreateAnImageOfVectors ${ITK_LIBRARIES})

install(TARGETS CreateAnImageOfVectors
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAnImageOfVectors/
  COMPONENT Code
  )


enable_testing()

add_test(NAME CreateAnImageOfVectorsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnImageOfVectors
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME CreateAnImageOfVectorsTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

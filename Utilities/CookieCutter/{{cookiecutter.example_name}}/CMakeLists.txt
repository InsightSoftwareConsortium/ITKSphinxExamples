cmake_minimum_required(VERSION 3.10.2)

project( {{ cookiecutter.example_name }} )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( {{ cookiecutter.example_name }} Code.cxx )
target_link_libraries( {{ cookiecutter.example_name }} ${ITK_LIBRARIES} )

install( TARGETS {{ cookiecutter.example_name }}
  DESTINATION bin/ITKSphinxExamples/{{ cookiecutter.group_name }}/{{ cookiecutter.module_name }}
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/{{ cookiecutter.group_name }}/{{ cookiecutter.module_name }}/{{ cookiecutter.example_name }}
  COMPONENT Code
)

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png)
set(output_image Output.png)
set(test_options)


add_test( NAME {{ cookiecutter.example_name }}Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/{{ cookiecutter.example_name }}
  ${input_image}
  ${output_image}
  ${test_options}
)

if( ITK_WRAP_PYTHON )
  find_package(PythonInterp REQUIRED)
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME {{ cookiecutter.example_name }}TestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()

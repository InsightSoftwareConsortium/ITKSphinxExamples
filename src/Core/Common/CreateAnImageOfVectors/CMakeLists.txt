cmake_minimum_required(VERSION 3.22.1)

project(CreateAnImageOfVectors)

find_package(ITK REQUIRED)


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAnImageOfVectors/
  COMPONENT Code
  )


enable_testing()

add_test(NAME CreateAnImageOfVectorsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  )

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME CreateAnImageOfVectorsTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

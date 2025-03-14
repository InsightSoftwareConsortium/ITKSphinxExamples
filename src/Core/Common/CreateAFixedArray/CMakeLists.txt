cmake_minimum_required(VERSION 3.22.1)

project(CreateAFixedArray)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx Code.py)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAFixedArray
  COMPONENT Code
)

enable_testing()
add_test(NAME CreateAFixedArrayTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateAFixedArrayTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

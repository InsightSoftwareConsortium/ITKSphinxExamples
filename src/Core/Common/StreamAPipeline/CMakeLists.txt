cmake_minimum_required(VERSION 3.16.3)

project(StreamAPipeline)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/StreamAPipeline
  COMPONENT Code
  )

enable_testing()
add_test(NAME StreamAPipelineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    3
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME StreamAPipelineTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      3
    )
endif()

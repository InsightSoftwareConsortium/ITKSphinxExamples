cmake_minimum_required(VERSION 3.16.3)

project(ReadAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase/
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ReadAnImage
  COMPONENT Code
  )

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png)

enable_testing()
add_test(NAME ReadAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME  ReadAnImageTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
    )
endif()

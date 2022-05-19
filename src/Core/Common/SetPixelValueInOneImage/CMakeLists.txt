cmake_minimum_required(VERSION 3.16.3)

project(SetPixelValueInOneImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(SetPixelValueInOneImage Code.cxx)
target_link_libraries(SetPixelValueInOneImage ${ITK_LIBRARIES})

install(TARGETS SetPixelValueInOneImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/SetPixelValueInOneImage
  COMPONENT Code
)

enable_testing()
add_test(NAME SetPixelValueInOneImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SetPixelValueInOneImage
  ${CMAKE_CURRENT_BINARY_DIR}/Output.png
)

if(ITK_WRAP_PYTHON)
  add_test(NAME SetPixelValueInOneImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${CMAKE_CURRENT_BINARY_DIR}/OutputPython.png
    )
endif()

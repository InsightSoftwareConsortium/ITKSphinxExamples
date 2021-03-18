cmake_minimum_required(VERSION 3.10.2)
project(CreateAnRGBImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(CreateAnRGBImage Code.cxx)
target_link_libraries(CreateAnRGBImage ${ITK_LIBRARIES})

install(TARGETS CreateAnRGBImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateAnRGBImage
  COMPONENT Code
)

enable_testing()
add_test(NAME CreateAnRGBImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAnRGBImage)

if(ITK_WRAP_PYTHON)
  add_test( NAME CreateAnRGBImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

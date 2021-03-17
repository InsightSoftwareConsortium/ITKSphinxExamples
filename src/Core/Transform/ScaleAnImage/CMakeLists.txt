cmake_minimum_required(VERSION 3.16.3)

project(ScaleAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ScaleAnImage Code.cxx)
target_link_libraries(ScaleAnImage ${ITK_LIBRARIES})

install(TARGETS ScaleAnImage
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )
  
install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/ScaleAnImage/
  COMPONENT Code
  )


enable_testing()

add_test(NAME ScaleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ScaleAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageInput.png
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageOutput.png
  )

if(ITK_WRAP_PYTHON)
add_test(NAME ScaleAnImageTestPython
COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageInput.png
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageOutputPython.png)
endif()

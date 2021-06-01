cmake_minimum_required(VERSION 3.10.2)

project(ThinImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ThinImage Code.cxx)
target_link_libraries(ThinImage ${ITK_LIBRARIES})

install(TARGETS ThinImage
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/ThinImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ThinImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ThinImage)

if(ITK_WRAP_PYTHON)
add_test(NAME ThinImageTestPython
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()

cmake_minimum_required(VERSION 3.16.3)

project(RegisterTwoPointSets)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegisterTwoPointSets Code.cxx)
target_link_libraries(RegisterTwoPointSets ${ITK_LIBRARIES})

install(TARGETS RegisterTwoPointSets
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/RegisterTwoPointSets/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RegisterTwoPointSetsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegisterTwoPointSets)
  
if(ITK_WRAP_PYTHON)
  add_test(NAME RegisterTwoPointSetsTest2DPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py 2
    )
    add_test(NAME RegisterTwoPointSetsTest3DPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py 3)
endif()

cmake_minimum_required(VERSION 3.16.3)

project(CreateForwardDifferenceKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateForwardDifferenceKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateForwardDifferenceKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

if(ITK_WRAP_PYTHON)
  add_test(NAME CreateForwardDifferenceKernelTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

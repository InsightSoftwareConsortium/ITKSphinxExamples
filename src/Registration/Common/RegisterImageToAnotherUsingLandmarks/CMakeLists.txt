cmake_minimum_required(VERSION 3.16.3)

project(RegisterImageToAnotherUsingLandmarks)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegisterImageToAnotherUsingLandmarks Code.cxx)
target_link_libraries(RegisterImageToAnotherUsingLandmarks ${ITK_LIBRARIES})

install(TARGETS RegisterImageToAnotherUsingLandmarks
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/RegisterImageToAnotherUsingLandmarks/
  COMPONENT Code
  )

enable_testing()
add_test(NAME RegisterImageToAnotherUsingLandmarksTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegisterImageToAnotherUsingLandmarks)

if(ITK_WRAP_PYTHON)
  add_test(NAME RegisterImageToAnotherUsingLandmarksTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

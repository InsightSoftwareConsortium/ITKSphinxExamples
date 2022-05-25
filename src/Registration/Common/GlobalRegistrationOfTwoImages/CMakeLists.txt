cmake_minimum_required(VERSION 3.16.3)

project(GlobalRegistrationOfTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GlobalRegistrationOfTwoImages Code.cxx)
target_link_libraries(GlobalRegistrationOfTwoImages ${ITK_LIBRARIES})

install(TARGETS GlobalRegistrationOfTwoImages
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/GlobalRegistrationOfTwoImages/
  COMPONENT Code
  )


enable_testing()

add_test(NAME GlobalRegistrationOfTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GlobalRegistrationOfTwoImages)

if( ITK_WRAP_PYTHON )
  add_test( NAME GlobalRegistrationOfTwoImagesTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    )
endif()

cmake_minimum_required(VERSION 3.10.2)

project(GlobalRegistrationOfTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GlobalRegistrationOfTwoImages Code.cxx)
target_link_libraries(GlobalRegistrationOfTwoImages ${ITK_LIBRARIES})

install(TARGETS GlobalRegistrationOfTwoImages
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/GlobalRegistrationOfTwoImages/
  COMPONENT Code
  )


enable_testing()

add_test(NAME GlobalRegistrationOfTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GlobalRegistrationOfTwoImages)

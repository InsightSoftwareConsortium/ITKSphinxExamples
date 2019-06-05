cmake_minimum_required(VERSION 3.10.2)

project(GlobalRegistrationTwoImagesAffine)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GlobalRegistrationTwoImagesAffine Code.cxx)
target_link_libraries(GlobalRegistrationTwoImagesAffine ${ITK_LIBRARIES})

install(TARGETS GlobalRegistrationTwoImagesAffine
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/GlobalRegistrationTwoImagesAffine/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GlobalRegistrationTwoImagesAffineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GlobalRegistrationTwoImagesAffine)

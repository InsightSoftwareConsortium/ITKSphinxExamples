cmake_minimum_required(VERSION 3.10.2)

project(TranslateAVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(TranslateAVectorImage Code.cxx)
target_link_libraries(TranslateAVectorImage ${ITK_LIBRARIES})

install(TARGETS TranslateAVectorImage
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/TranslateAVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME TranslateAVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TranslateAVectorImage)


cmake_minimum_required(VERSION 3.10.2)

project(DisplayITKImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DisplayITKImage Code.cxx)
target_link_libraries(DisplayITKImage ${ITK_LIBRARIES})

install(TARGETS DisplayITKImage
  DESTINATION bin/ITKSphinxExamples/Remote/WikiExamples
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Remote/WikiExamples/DisplayITKImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DisplayITKImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DisplayITKImage)

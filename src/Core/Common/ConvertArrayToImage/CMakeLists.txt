cmake_minimum_required(VERSION 3.10.2)

project(ConvertArrayToImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertArrayToImage Code.cxx)
target_link_libraries(ConvertArrayToImage ${ITK_LIBRARIES})

install(TARGETS ConvertArrayToImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Core/Common/ConvertArrayToImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertArrayToImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertArrayToImage
  )

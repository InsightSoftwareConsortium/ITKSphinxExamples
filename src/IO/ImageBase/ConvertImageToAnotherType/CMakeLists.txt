cmake_minimum_required(VERSION 3.10.2)

project(ConvertImageToAnotherType)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertImageToAnotherType Code.cxx)
target_link_libraries(ConvertImageToAnotherType ${ITK_LIBRARIES})

install(TARGETS ConvertImageToAnotherType
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ConvertImageToAnotherType/
  COMPONENT Code
  )

enable_testing()
add_test(NAME ConvertImageToAnotherTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertImageToAnotherType
  )


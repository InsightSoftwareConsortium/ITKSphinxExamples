cmake_minimum_required(VERSION 3.10.2)

project(CastImageToAnotherTypeButClampToOutput)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CastImageToAnotherTypeButClampToOutput Code.cxx)
target_link_libraries(CastImageToAnotherTypeButClampToOutput ${ITK_LIBRARIES})

install(TARGETS CastImageToAnotherTypeButClampToOutput
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/CastImageToAnotherTypeButClampToOutput/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CastImageToAnotherTypeButClampToOutputTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CastImageToAnotherTypeButClampToOutput)


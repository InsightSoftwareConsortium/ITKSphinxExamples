cmake_minimum_required(VERSION 3.16.3)

project(CustomUserMatrixToAlignImageWithDICOM)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CustomUserMatrixToAlignImageWithDICOM Code.cxx)
target_link_libraries(CustomUserMatrixToAlignImageWithDICOM ${ITK_LIBRARIES})

install(TARGETS CustomUserMatrixToAlignImageWithDICOM
  DESTINATION bin/ITKSphinxExamples/Remote/WikiExamples
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Remote/WikiExamples/CustomUserMatrixToAlignImageWithDICOM/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CustomUserMatrixToAlignImageWithDICOMTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CustomUserMatrixToAlignImageWithDICOM)


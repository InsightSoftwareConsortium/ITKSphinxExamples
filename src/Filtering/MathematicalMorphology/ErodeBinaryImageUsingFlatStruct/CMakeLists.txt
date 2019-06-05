cmake_minimum_required(VERSION 3.10.2)

project(ErodeBinaryImageUsingFlatStruct)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ErodeBinaryImageUsingFlatStruct Code.cxx)
target_link_libraries(ErodeBinaryImageUsingFlatStruct ${ITK_LIBRARIES})

install(TARGETS ErodeBinaryImageUsingFlatStruct
  DESTINATION bin/ITKExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/MathematicalMorphology/ErodeBinaryImageUsingFlatStruct/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ErodeBinaryImageUsingFlatStructTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ErodeBinaryImageUsingFlatStruct)

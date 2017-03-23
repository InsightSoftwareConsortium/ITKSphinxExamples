cmake_minimum_required(VERSION 2.8.9)

project(ImportPixelBufferIntoAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ImportPixelBufferIntoAnImage Code.cxx)
target_link_libraries(ImportPixelBufferIntoAnImage ${ITK_LIBRARIES})

install(TARGETS ImportPixelBufferIntoAnImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Core/Common/ImportPixelBufferIntoAnImage/
  COMPONENT Code
  )


enable_testing()
set(output_image Output.png)
set(test_options)

add_test(NAME ImportPixelBufferIntoAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImportPixelBufferIntoAnImage
    ${output_image}
    ${test_options}
  )

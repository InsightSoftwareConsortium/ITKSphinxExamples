cmake_minimum_required(VERSION 3.16.3)

project(TransformVectorValuedImagePixels)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(TransformVectorValuedImagePixels Code.cxx)
target_link_libraries(TransformVectorValuedImagePixels ${ITK_LIBRARIES})

install(TARGETS TransformVectorValuedImagePixels
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/TransformVectorValuedImagePixels/
  COMPONENT Code
  )


enable_testing()
add_test(NAME TransformVectorValuedImagePixelsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TransformVectorValuedImagePixels
    Gourds.png
    output.png
  )

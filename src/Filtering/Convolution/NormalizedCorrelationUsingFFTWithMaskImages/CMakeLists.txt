cmake_minimum_required(VERSION 3.10.2)

project(NormalizedCorrelationUsingFFTWithMaskImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizedCorrelationUsingFFTWithMaskImages Code.cxx)
target_link_libraries(NormalizedCorrelationUsingFFTWithMaskImages ${ITK_LIBRARIES})

install(TARGETS NormalizedCorrelationUsingFFTWithMaskImages
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Convolution/NormalizedCorrelationUsingFFTWithMaskImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NormalizedCorrelationUsingFFTWithMaskImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizedCorrelationUsingFFTWithMaskImages)

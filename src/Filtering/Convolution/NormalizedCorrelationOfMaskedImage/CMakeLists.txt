cmake_minimum_required(VERSION 3.10.2)

project(NormalizedCorrelationOfMaskedImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizedCorrelationOfMaskedImage Code.cxx)
target_link_libraries(NormalizedCorrelationOfMaskedImage ${ITK_LIBRARIES})

install(TARGETS NormalizedCorrelationOfMaskedImage
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Convolution/NormalizedCorrelationOfMaskedImage/
  COMPONENT Code
  )

enable_testing()
add_test(NAME NormalizedCorrelationOfMaskedImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizedCorrelationOfMaskedImage

  )

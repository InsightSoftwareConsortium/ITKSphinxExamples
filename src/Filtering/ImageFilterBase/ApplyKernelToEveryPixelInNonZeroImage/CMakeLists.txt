cmake_minimum_required(VERSION 3.10.2)

project(ApplyKernelToEveryPixelInNonZeroImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ApplyKernelToEveryPixelInNonZeroImage Code.cxx)
target_link_libraries(ApplyKernelToEveryPixelInNonZeroImage ${ITK_LIBRARIES})

install(TARGETS ApplyKernelToEveryPixelInNonZeroImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFilterBase/ApplyKernelToEveryPixelInNonZeroImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ApplyKernelToEveryPixelInNonZeroImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyKernelToEveryPixelInNonZeroImage)

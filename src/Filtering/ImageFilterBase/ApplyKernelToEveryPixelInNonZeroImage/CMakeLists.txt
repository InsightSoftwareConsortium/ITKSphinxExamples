cmake_minimum_required(VERSION 3.22.1)

project(ApplyKernelToEveryPixelInNonZeroImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFilterBase/ApplyKernelToEveryPixelInNonZeroImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ApplyKernelToEveryPixelInNonZeroImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

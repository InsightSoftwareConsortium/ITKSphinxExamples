cmake_minimum_required(VERSION 3.10.2)

project(CustomOperationToCorrespondingPixelsInTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CustomOperationToCorrespondingPixelsInTwoImages Code.cxx)
target_link_libraries(CustomOperationToCorrespondingPixelsInTwoImages ${ITK_LIBRARIES})

install(TARGETS CustomOperationToCorrespondingPixelsInTwoImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFilterBase/CustomOperationToCorrespondingPixelsInTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CustomOperationToCorrespondingPixelsInTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CustomOperationToCorrespondingPixelsInTwoImages)

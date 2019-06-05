cmake_minimum_required(VERSION 3.10.2)

project(ExtractBoundariesOfBlobsInBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExtractBoundariesOfBlobsInBinaryImage Code.cxx)
target_link_libraries(ExtractBoundariesOfBlobsInBinaryImage ${ITK_LIBRARIES})

install(TARGETS ExtractBoundariesOfBlobsInBinaryImage
  DESTINATION bin/ITKExamples/Filtering/ImageLabel
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageLabel/ExtractBoundariesOfBlobsInBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtractBoundariesOfBlobsInBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractBoundariesOfBlobsInBinaryImage)


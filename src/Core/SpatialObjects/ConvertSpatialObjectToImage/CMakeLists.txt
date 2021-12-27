cmake_minimum_required(VERSION 3.16.3)

project(ConvertSpatialObjectToImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertSpatialObjectToImage Code.cxx)
target_link_libraries(ConvertSpatialObjectToImage ${ITK_LIBRARIES})

install(TARGETS ConvertSpatialObjectToImage
  DESTINATION bin/ITKSphinxExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/SpatialObjects/ConvertSpatialObjectToImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertSpatialObjectToImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertSpatialObjectToImage
    output.png)

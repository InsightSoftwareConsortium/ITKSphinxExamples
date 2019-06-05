cmake_minimum_required(VERSION 3.10.2)

project(ConvertSpacialObjectToImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertSpacialObjectToImage Code.cxx)
target_link_libraries(ConvertSpacialObjectToImage ${ITK_LIBRARIES})

install(TARGETS ConvertSpacialObjectToImage
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/ConvertSpacialObjectToImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertSpacialObjectToImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertSpacialObjectToImage)


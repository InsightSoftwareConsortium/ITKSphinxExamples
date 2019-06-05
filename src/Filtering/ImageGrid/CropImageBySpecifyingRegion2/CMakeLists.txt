cmake_minimum_required(VERSION 3.10.2)

project(CropImageBySpecifyingRegion2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CropImageBySpecifyingRegion2 Code.cxx)
target_link_libraries(CropImageBySpecifyingRegion2 ${ITK_LIBRARIES})

install(TARGETS CropImageBySpecifyingRegion2
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/CropImageBySpecifyingRegion2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CropImageBySpecifyingRegion2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CropImageBySpecifyingRegion2)

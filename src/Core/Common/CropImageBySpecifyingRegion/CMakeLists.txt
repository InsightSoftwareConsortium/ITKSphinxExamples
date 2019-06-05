cmake_minimum_required(VERSION 3.10.2)

project(CropImageBySpecifyingRegion)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CropImageBySpecifyingRegion Code.cxx)
target_link_libraries(CropImageBySpecifyingRegion ${ITK_LIBRARIES})

install(TARGETS CropImageBySpecifyingRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CropImageBySpecifyingRegion/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CropImageBySpecifyingRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CropImageBySpecifyingRegion)

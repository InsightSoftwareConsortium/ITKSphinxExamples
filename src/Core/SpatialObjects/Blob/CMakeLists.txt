cmake_minimum_required(VERSION 3.10.2)

project(Blob)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Blob Code.cxx)
target_link_libraries(Blob ${ITK_LIBRARIES})

install(TARGETS Blob
  DESTINATION bin/ITKSphinxExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/SpatialObjects/Blob/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BlobTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Blob)

cmake_minimum_required(VERSION 3.10.2)

project(StoreNonPixelDataInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(StoreNonPixelDataInImage Code.cxx)
target_link_libraries(StoreNonPixelDataInImage ${ITK_LIBRARIES})

install(TARGETS StoreNonPixelDataInImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/StoreNonPixelDataInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME StoreNonPixelDataInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StoreNonPixelDataInImage)

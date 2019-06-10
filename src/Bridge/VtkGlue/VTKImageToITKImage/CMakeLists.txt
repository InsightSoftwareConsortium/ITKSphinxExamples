cmake_minimum_required(VERSION 3.10.2)

project(VTKImageToITKImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(VTKImageToITKImage Code.cxx)
target_link_libraries(VTKImageToITKImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

install(TARGETS VTKImageToITKImage
  DESTINATION bin/ITKExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Bridge/VtkGlue/VTKImageToITKImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME VTKImageToITKImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VTKImageToITKImage)


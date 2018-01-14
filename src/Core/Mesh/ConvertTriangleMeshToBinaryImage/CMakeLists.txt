cmake_minimum_required(VERSION 3.8.2)

project( ConvertTriangleMeshToBinaryImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConvertTriangleMeshToBinaryImage Code.cxx )
target_link_libraries( ConvertTriangleMeshToBinaryImage ${ITK_LIBRARIES} )

install( TARGETS ConvertTriangleMeshToBinaryImage
  DESTINATION bin/ITKExamples/Core/Mesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Mesh/ConvertTriangleMeshToBinaryImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConvertTriangleMeshToBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertTriangleMeshToBinaryImage
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    ${CMAKE_CURRENT_BINARY_DIR}/torus.vtk
    ${CMAKE_CURRENT_BINARY_DIR}/Output.mha
)

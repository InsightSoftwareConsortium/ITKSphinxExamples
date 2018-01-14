cmake_minimum_required(VERSION 3.8.2)

project( ConvertAnITKGrayScaleImageToCVMat )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConvertAnITKGrayScaleImageToCVMat Code.cxx )
target_link_libraries( ConvertAnITKGrayScaleImageToCVMat ${ITK_LIBRARIES} )

install( TARGETS ConvertAnITKGrayScaleImageToCVMat
  DESTINATION bin/ITKExamples/Video/BridgeOpenCV
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Video/BridgeOpenCV/ConvertAnITKGrayScaleImageToCVMat
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConvertAnITKGrayScaleImageToCVMatTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertAnITKGrayScaleImageToCVMat
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output.png
)

cmake_minimum_required( VERSION 2.8 )

project( RegisterIOFactories )

find_package( ITK REQUIRED )
# Registering the IO classes manually is usually not necessary,
# unless this variable is set before calling
#   "include( ${ITK_USE_FILE} )"
set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include( ${ITK_USE_FILE} )

add_executable( RegisterIOFactories Code.cxx )
target_link_libraries( RegisterIOFactories ${ITK_LIBRARIES} )

install( TARGETS RegisterIOFactories
  DESTINATION bin/ITKExamples/IO/ImageBase
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/ImageBase/RegisterIOFactories
  COMPONENT Code
  )

enable_testing()
add_test( NAME RegisterIOFactoriesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegisterIOFactories
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png
  )

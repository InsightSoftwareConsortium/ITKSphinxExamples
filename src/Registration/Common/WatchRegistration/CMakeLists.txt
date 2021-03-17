cmake_minimum_required(VERSION 3.10.2)

project(WatchRegistration)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED
  COMPONENTS
    vtkRenderingCore
    vtkRenderingGL2PSOpenGL2
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(WatchRegistration Code.cxx)
target_link_libraries(WatchRegistration ${ITK_LIBRARIES} ${VTK_LIBRARIES})

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS WatchRegistration
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS WatchRegistration
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/WatchRegistration/
  COMPONENT Code
  )


enable_testing()
add_test(NAME WatchRegistrationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WatchRegistration fixed.png moving.png)


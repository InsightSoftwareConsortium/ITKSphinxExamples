cmake_minimum_required(VERSION 3.16.3)

project(SignedDistanceMapOfBinary)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


if(ENABLE_QUICKVIEW)
  find_package(VTK REQUIRED
    COMPONENTS
      ${_vtk_prefix}RenderingCore
      ${_vtk_prefix}RenderingGL2PSOpenGL2
    )

  if(VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()

  add_executable(SignedDistanceMapOfBinary Code.cxx)
  target_link_libraries(SignedDistanceMapOfBinary ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS SignedDistanceMapOfBinary
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(SignedDistanceMapOfBinary Code.cxx)
  target_link_libraries(SignedDistanceMapOfBinary ${ITK_LIBRARIES})
endif()

install(TARGETS SignedDistanceMapOfBinary
  DESTINATION bin/ITKSphinxExamples/Filtering/DistanceMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/DistanceMap/SignedDistanceMapOfBinary/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SignedDistanceMapOfBinaryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SignedDistanceMapOfBinary)


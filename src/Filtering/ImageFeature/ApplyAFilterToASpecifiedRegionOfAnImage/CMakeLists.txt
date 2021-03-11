cmake_minimum_required(VERSION 3.10.2)

project(ApplyAFilterToASpecifiedRegionOfAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


if(ENABLE_QUICKVIEW)
  find_package(VTK REQUIRED
    COMPONENTS
      vtkRenderingCore
      vtkRenderingGL2PSOpenGL2
    )

  if(VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()

  add_executable(ApplyAFilterToASpecifiedRegionOfAnImage Code.cxx)
  target_link_libraries(ApplyAFilterToASpecifiedRegionOfAnImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS ApplyAFilterToASpecifiedRegionOfAnImage
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(ApplyAFilterToASpecifiedRegionOfAnImage Code.cxx)
  target_link_libraries(ApplyAFilterToASpecifiedRegionOfAnImage ${ITK_LIBRARIES})
endif()

install(TARGETS ApplyAFilterToASpecifiedRegionOfAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/ApplyAFilterToASpecifiedRegionOfAnImage/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)
set(output_image Output.png)
set(test_options)

add_test(NAME ApplyAFilterOnlyToASpecifiedRegionOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAFilterOnlyToASpecifiedRegionOfAnImage
    ${input_image}
    ${output_image}
    ${test_options}
  )

cmake_minimum_required(VERSION 3.10.2)

project(SegmentPixelsWithSimilarStats)

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

  add_executable(SegmentPixelsWithSimilarStats Code.cxx)
  target_link_libraries(SegmentPixelsWithSimilarStats ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS SegmentPixelsWithSimilarStats
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(SegmentPixelsWithSimilarStats Code.cxx)
  target_link_libraries(SegmentPixelsWithSimilarStats ${ITK_LIBRARIES})
endif()

install(TARGETS SegmentPixelsWithSimilarStats
  DESTINATION bin/ITKExamples/Segmentation/RegionGrowing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/RegionGrowing/SegmentPixelsWithSimilarStats/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png)

add_test(NAME SegmentPixelsWithSimilarStatsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentPixelsWithSimilarStats
    ${input_image}
    100
    50
  )
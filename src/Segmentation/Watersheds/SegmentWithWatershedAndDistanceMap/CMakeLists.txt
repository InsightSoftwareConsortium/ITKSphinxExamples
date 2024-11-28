cmake_minimum_required(VERSION 3.10.2)

project(SegmentWithWatershedAndDistanceMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SegmentWithWatershedAndDistanceMap Code.cxx)
target_link_libraries(SegmentWithWatershedAndDistanceMap ${ITK_LIBRARIES})

install(TARGETS SegmentWithWatershedAndDistanceMap
  DESTINATION bin/ITKExamples/Segmentation/Watersheds
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Segmentation/Watersheds/SegmentWithWatershedAndDistanceMap/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/PlateauBorder.tif)
set(binarizingRadius01 2)
set(majorityThreshold01 2)
set(watershedThreshold01 0.01)
set(watershedLevel01 0.5)
set(cleaningStructuringElementRadius01 3)

add_test(NAME SegmentWithWatershedAndDistanceMapTest01
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentWithWatershedAndDistanceMap
    ${input_image}
    ReversedInputImageTest01.tif
    DistanceMapImageTest01.tif
    WatershedImageTest01.tif
    SegmentWithWatershedAndDistanceMapTest01.tif
    ${binarizingRadius01}
    ${majorityThreshold01}
    ${watershedThreshold01}
    ${watershedLevel01}
    ${cleaningStructuringElementRadius01}
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME SegmentWithWatershedAndDistanceMapTest01Python
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ReversedInputImageTest01.tif
      DistanceMapImageTest01.tif
      WatershedImageTest01.tif
      SegmentWithWatershedAndDistanceMapTest01Python.tif
      ${binarizingRadius01}
      ${majorityThreshold01}
      ${watershedThreshold01}
      ${watershedLevel01}
      ${cleaningStructuringElementRadius01}
    )
endif()

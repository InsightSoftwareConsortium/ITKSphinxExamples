cmake_minimum_required(VERSION 3.22.1)

project(ComputePlanarParameterizationOfAMesh)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/QuadEdgeMeshFiltering/ComputePlanarParameterizationOfAMesh
  COMPONENT Code
  )

enable_testing()

foreach(border 0 1)
  foreach(coeff 0 1 2 3 4)
    add_test(NAME ComputePlanarParameterizationOfAMeshTestb${border}_c${coeff}
      COMMAND ComputePlanarParameterizationOfAMesh
        ${CMAKE_CURRENT_BINARY_DIR}/mushroom.vtk ${border} ${coeff}
            param_border${border}_coeff${coeff}_solver${solver}.vtk)
  endforeach()
endforeach()

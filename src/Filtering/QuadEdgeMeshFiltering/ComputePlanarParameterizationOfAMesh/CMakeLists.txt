cmake_minimum_required( VERSION 2.8.6 )

project( ComputePlanarParameterizationOfAMesh )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputePlanarParameterizationOfAMesh Code.cxx )
target_link_libraries( ComputePlanarParameterizationOfAMesh ${ITK_LIBRARIES} )

install( TARGETS ComputePlanarParameterizationOfAMesh
  DESTINATION bin/ITKExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/QuadEdgeMeshFiltering/ComputePlanarParameterizationOfAMesh
  COMPONENT Code
  )

enable_testing()

foreach( border 0 1 )
  foreach( coeff 0 1 2 3 4 )
    add_test(NAME ComputePlanarParameterizationOfAMeshTestb${border}_c${coeff}
      COMMAND ComputePlanarParameterizationOfAMesh
        ${CMAKE_CURRENT_BINARY_DIR}/mushroom.vtk ${border} ${coeff}
            param_border${border}_coeff${coeff}_solver${solver}.vtk)
  endforeach()
endforeach()

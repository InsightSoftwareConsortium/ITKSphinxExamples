add_example( ConvertTriangleMeshToBinaryImage )
compare_to_baseline(
  EXAMPLE_NAME ConvertTriangleMeshToBinaryImage
  BASELINE_PREFIX OutputBaseline )

add_example( ExtractIsoSurface )
#compare_to_baseline( ExtractIsoSurface Output )

add_example( TranslateOneMesh )
#compare_to_baseline( TranslateOneMesh Output )

add_example(AccessDataInCells)

add_example(AddPointsAndEdges)
add_example(CalculateAreaAndVolumeOfSimplexMesh)

add_example(WriteMeshToVTP)
add_example(WorkingWithPointAndCellData)

if(VTK_DIR)
  add_example(ConvertMeshToUnstructeredGrid)
  #TODO: Fix Baseline Comparison
  #compare_to_baseline(EXAMPLE_NAME ConvertMeshToUnstructeredGrid
  #  BASELINE_PREFIX OutputBaseline
  #  )
endif()

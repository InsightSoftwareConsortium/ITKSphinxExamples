add_example( ConvertTriangleMeshToBinaryImage )
compare_to_baseline(
  EXAMPLE_NAME ConvertTriangleMeshToBinaryImage
  BASELINE_PREFIX OutputBaseline )

add_example( ExtractIsoSurface )
#compare_to_baseline( ExtractIsoSurface Output )

add_example( TranslateOneMesh )
#compare_to_baseline( TranslateOneMesh Output )

add_example(AddPointsAndEdges)
compare_to_baseline(EXAMPLE_NAME AddPointsAndEdges
  BASELINE_PREFIX OutputBaseline
  )

add_example(CalculateAreaAndVolumeOfSimplexMesh)
compare_to_baseline(EXAMPLE_NAME CalculateAreaAndVolumeOfSimplexMesh
  BASELINE_PREFIX OutputBaseline
  )

add_example(WriteMeshToVTP)
compare_to_baseline(EXAMPLE_NAME WriteMeshToVTP
  BASELINE_PREFIX OutputBaseline
  )

add_example(WorkingWithPointAndCellData)
compare_to_baseline(EXAMPLE_NAME WorkingWithPointAndCellData
  BASELINE_PREFIX OutputBaseline
  )

if(ENABLE_QUICKVIEW)
add_example(ConvertMeshToUnstructeredGrid)
compare_to_baseline(EXAMPLE_NAME ConvertMeshToUnstructeredGrid
  BASELINE_PREFIX OutputBaseline
  )
endif()

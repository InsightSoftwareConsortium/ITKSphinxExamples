add_example( ComputeNormalsOfAMesh )
add_example( CleanQuadEdgeMesh )
compare_to_baseline( EXAMPLE_NAME CleanQuadEdgeMesh
        BASELINE_PREFIX OutputBaseline)
add_example( DelaunayConformEdgeFlipping )
# compare_to_baseline( DelaunayConformEdgeFlipping Output)

add_example( ComputePlanarParameterizationOfAMesh )

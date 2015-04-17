add_example( MaskOneImageGivenLabelMap )
compare_to_baseline( EXAMPLE_NAME MaskOneImageGivenLabelMap BASELINE_PREFIX Output1Baseline )

add_example( RemoveHolesNotConnectedToImageBoundaries )
compare_to_baseline( EXAMPLE_NAME RemoveHolesNotConnectedToImageBoundaries BASELINE_PREFIX OutputBaseline )

add_example( ExtractGivenLabelObject )
compare_to_baseline( EXAMPLE_NAME ExtractGivenLabelObject
  TEST_NAME ExtractGivenLabelObjectTestBaselineComparison1
  DEPENDS ExtractGivenLabelObjectTest
  BASELINE_PREFIX Output1Baseline
  TEST_IMAGE Output1.png
)
compare_to_baseline( EXAMPLE_NAME ExtractGivenLabelObject
  TEST_NAME ExtractGivenLabelObjectTestBaselineComparison2
  DEPENDS ExtractGivenLabelObjectTest
  BASELINE_PREFIX Output2Baseline
  TEST_IMAGE Output2.png
)

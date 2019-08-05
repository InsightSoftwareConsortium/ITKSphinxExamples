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

add_example( ApplyMorphologicalClosingOnAllLabelObjects )
compare_to_baseline( EXAMPLE_NAME ApplyMorphologicalClosingOnAllLabelObjects BASELINE_PREFIX OutputBaseline )

add_example( ApplyMorphologicalClosingOnSpecificLabelObject )
compare_to_baseline( EXAMPLE_NAME ApplyMorphologicalClosingOnSpecificLabelObject BASELINE_PREFIX OutputBaseline )

add_example(RemoveLabelsFromLabelMap)

add_example(KeepRegionsThatMeetSpecific)
compare_to_baseline(EXAMPLE_NAME KeepRegionsThatMeetSpecific
  BASELINE_PREFIX output
  )

add_example(KeepRegionsAboveLevel)
compare_to_baseline(EXAMPLE_NAME KeepRegionsAboveLevel
  BASELINE_PREFIX output
  )

add_example(KeepBinaryRegionsThatMeetSpecific)
compare_to_baseline(EXAMPLE_NAME KeepBinaryRegionsThatMeetSpecific
  BASELINE_PREFIX output
  )

add_example(LabelBinaryRegionsInImage)
compare_to_baseline(EXAMPLE_NAME LabelBinaryRegionsInImage
  BASELINE_PREFIX image
  )

add_example(LabelBinaryRegionsAndGetProperties)
compare_to_baseline(EXAMPLE_NAME LabelBinaryRegionsAndGetProperties
  BASELINE_PREFIX image
  )

add_example(ConvertLabelMapToImage)
compare_to_baseline(EXAMPLE_NAME ConvertLabelMapToImage
  BASELINE_PREFIX image
  )

add_example(MergeLabelMaps)
add_example(ConvertImageWithLabelsToShapeLabelMap)
add_example(ShapeAttributesForBinaryImage)

add_example(InvertImageUsingBinaryNot)
compare_to_baseline(EXAMPLE_NAME InvertImageUsingBinaryNot
  BASELINE_PREFIX output
  )

add_example(ConvertImageToLabelMap)

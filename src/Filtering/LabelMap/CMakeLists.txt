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
compare_to_baseline(EXAMPLE_NAME RemoveLabelsFromLabelMap
  BASELINE_PREFIX OutputBaseline
  )

add_example(KeepRegionsThatMeetSpecific)
compare_to_baseline(EXAMPLE_NAME KeepRegionsThatMeetSpecific
  BASELINE_PREFIX OutputBaseline
  )

add_example(KeepRegionsAboveLevel)
compare_to_baseline(EXAMPLE_NAME KeepRegionsAboveLevel
  BASELINE_PREFIX OutputBaseline
  )

add_example(KeepBinaryRegionsThatMeetSpecific)
compare_to_baseline(EXAMPLE_NAME KeepBinaryRegionsThatMeetSpecific
  BASELINE_PREFIX OutputBaseline
  )

add_example(LabelBinaryRegionsInImage)
compare_to_baseline(EXAMPLE_NAME LabelBinaryRegionsInImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(LabelBinaryRegionsAndGetProperties)
compare_to_baseline(EXAMPLE_NAME LabelBinaryRegionsAndGetProperties
  BASELINE_PREFIX OutputBaseline
  )

add_example(ConvertLabelMapToImage)
compare_to_baseline(EXAMPLE_NAME ConvertLabelMapToImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(MergeLabelMaps)
compare_to_baseline(EXAMPLE_NAME MergeLabelMaps
  BASELINE_PREFIX OutputBaseline
  )

add_example(ConvertImageWithLabelsToShapeLabelMap)
compare_to_baseline(EXAMPLE_NAME ConvertImageWithLabelsToShapeLabelMap
  BASELINE_PREFIX OutputBaseline
  )

add_example(ShapeAttributesForBinaryImage)
compare_to_baseline(EXAMPLE_NAME ShapeAttributesForBinaryImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(InvertImageUsingBinaryNot)
compare_to_baseline(EXAMPLE_NAME InvertImageUsingBinaryNot
  BASELINE_PREFIX OutputBaseline
  )

add_example(ConvertImageToLabelMap)
compare_to_baseline(EXAMPLE_NAME ConvertImageToLabelMap
  BASELINE_PREFIX OutputBaseline
  )

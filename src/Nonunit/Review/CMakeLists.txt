add_example(SegmentBloodVesselsWithMultiScaleHessianBasedMeasure)
compare_to_baseline(EXAMPLE_NAME SegmentBloodVesselsWithMultiScaleHessianBasedMeasure
  BASELINE_PREFIX OutputBaseline)

# TODO: Examples below contain errors from original Wiki
#add_example(MultiphaseChanAndVeseSparseFieldLevelSetSegmentation)
#compare_to_baseline(EXAMPLE_NAME MultiphaseChanAndVeseSparseFieldLevelSetSegmentation
#  BASELINE_PREFIX OutputBaseline
#  )

#add_example(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation)
#compare_to_baseline(EXAMPLE_NAME SinglephaseChanAndVeseSparseFieldLevelSetSegmentation
#  BASELINE_PREFIX OutputBaseline
#  )

#add_example(SinglephaseChanAndVeseDenseFieldLevelSetSegmentation)
#compare_to_baseline(EXAMPLE_NAME SinglephaseChanAndVeseDenseFieldLevelSetSegmentation
#  BASELINE_PREFIX OutputBaseline
#  )

add_example(GeometricPropertiesOfRegion)
#TODO: Save output ITK image and then use it to compare to baseline
#compare_to_baseline(EXAMPLE_NAME GeometricPropertiesOfRegion
#        BASELINE_PREFIX OutputBaseline
#        )
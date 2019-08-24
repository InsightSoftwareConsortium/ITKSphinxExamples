if(ENABLE_QUICKVIEW)

# TODO Fix build errors
#add_example(LabelConnectComponentsInBinaryImage)
#compare_to_baseline(EXAMPLE_NAME LabelConnectComponentsInBinaryImage
#  BASELINE_PREFIX OutputBaseline
#  )
#================================

add_example(LabelConnectComponentsInGrayscaleImage)
compare_to_baseline(EXAMPLE_NAME LabelConnectComponentsInGrayscaleImage
  BASELINE_PREFIX LabelConnectComponentsInGrayscaleImage
  )

add_example(AssignContiguousLabelsToConnectedRegions)
compare_to_baseline(EXAMPLE_NAME AssignContiguousLabelsToConnectedRegions
  BASELINE_PREFIX AssignContiguousLabelsToConnectedRegions
  )

add_example(ExtraLargestConnectComponentFromBinaryImage)
compare_to_baseline(EXAMPLE_NAME ExtraLargestConnectComponentFromBinaryImage
  BASELINE_PREFIX ExtraLargestConnectComponentFromBinaryImage
  )

endif()
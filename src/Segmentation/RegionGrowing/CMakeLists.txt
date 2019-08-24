if(ENABLE_QUICKVIEW)

add_example(SegmentPixelsWithSimilarStats)
compare_to_baseline(EXAMPLE_NAME ConnectedComponentsInImage
  BASELINE_PREFIX SegmentPixelsWithSimilarStats
  )

endif()

# TODO: incomplete example needs code fixes
# add_example(ConnectedComponentsInImage)
# compare_to_baseline(EXAMPLE_NAME ConnectedComponentsInImage
#  BASELINE_PREFIX OutputBaseline
#  )


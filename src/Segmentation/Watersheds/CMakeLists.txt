
add_example(SegmentWithWatershedImageFilter)

foreach( i RANGE 1 5 )
  compare_to_baseline(
    EXAMPLE_NAME SegmentWithWatershedImageFilter
    TEST_NAME SegmentWithWatershedImageFilterTest0${i}BaselineComparison
    TEST_IMAGE SegmentWithWatershedImageFilterTest0${i}.png
    BASELINE_PREFIX SegmentWithWatershedImageFilterTest0${i}Baseline
    DEPENDS SegmentWithWatershedImageFilterTest0${i}
  )
endforeach()

add_example(MorphologicalWatershedSegmentation)
compare_to_baseline(EXAMPLE_NAME MorphologicalWatershedSegmentation
  BASELINE_PREFIX OutputBaseline
  )

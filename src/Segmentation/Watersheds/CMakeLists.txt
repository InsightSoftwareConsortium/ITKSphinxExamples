
add_example(SegmentWithWatershedAndDistanceMap)
compare_to_baseline(EXAMPLE_NAME SegmentWithWatershedAndDistanceMap
  TEST_NAME SegmentWithWatershedAndDistanceMapTest01BaselineComparison
  BASELINE_PREFIX SegmentWithWatershedAndDistanceMapTest01Baseline
  DEPENDS SegmentWithWatershedAndDistanceMapTest01
  TEST_IMAGE SegmentWithWatershedAndDistanceMapTest01.png
  )

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
  BASELINE_PREFIX output_20_3
  )

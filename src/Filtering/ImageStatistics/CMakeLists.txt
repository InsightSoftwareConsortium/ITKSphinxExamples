add_example( ApplyAccumulateImageFilter )

foreach( i RANGE 0 2 )
  compare_to_baseline(
    EXAMPLE_NAME ApplyAccumulateImageFilter
    TEST_NAME ApplyAccumulateImageFilterTest${i}BaselineComparison
    TEST_IMAGE_PREFIX ApplyAccumulateImageFilterTestOutput${i}
    BASELINE_PREFIX Output${i}Baseline
    DEPENDS ApplyAccumulateImageFilterTest${i}
  )
endforeach()

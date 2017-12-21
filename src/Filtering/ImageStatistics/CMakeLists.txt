
add_example(AdaptiveHistogramEqualizationImageFilter)
compare_to_baseline(EXAMPLE_NAME AdaptiveHistogramEqualizationImageFilter
  TEST_NAME AdaptiveHistogramEqualizationImageFilterTest01BaselineComparison
  BASELINE_PREFIX AdaptiveHistogramEqualizationImageFilter01Baseline
  DEPENDS AdaptiveHistogramEqualizationImageFilterTest01
  TEST_IMAGE AdaptiveHistogramEqualizationImageFilterTest01.png
  )

add_example( ApplyAccumulateImageFilter )

foreach( i RANGE 0 2 )
  compare_to_baseline(
    EXAMPLE_NAME ApplyAccumulateImageFilter
    TEST_NAME ApplyAccumulateImageFilterTest${i}BaselineComparison
    TEST_IMAGE ApplyAccumulateImageFilterTestOutput${i}.mha
    BASELINE_PREFIX Output${i}Baseline
    DEPENDS ApplyAccumulateImageFilterTest${i}
  )
endforeach()

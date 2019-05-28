
add_example(AdaptiveHistogramEqualizationImageFilter)

foreach( i RANGE 1 6 )
  compare_to_baseline(
    EXAMPLE_NAME AdaptiveHistogramEqualizationImageFilter
    TEST_NAME AdaptiveHistogramEqualizationImageFilterTest0${i}BaselineComparison
    TEST_IMAGE AdaptiveHistogramEqualizationImageFilterTest0${i}.png
    BASELINE_PREFIX AdaptiveHistogramEqualizationImageFilter0${i}Baseline
    OPTIONS --tolerance-intensity 1
    DEPENDS AdaptiveHistogramEqualizationImageFilterTest0${i}
  )

  # compare_to_baseline(
    # EXAMPLE_NAME AdaptiveHistogramEqualizationImageFilter
    # TEST_NAME AdaptiveHistogramEqualizationImageFilterTest0${i}Baseline_histogramComparison
    # TEST_IMAGE AdaptiveHistogramEqualizationImageFilterTest0${i}_histogram.png
    # BASELINE_PREFIX AdaptiveHistogramEqualizationImageFilter0${i}Baseline_histogram
    # DEPENDS AdaptiveHistogramEqualizationImageFilterTest0${i}
  # )
endforeach()

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

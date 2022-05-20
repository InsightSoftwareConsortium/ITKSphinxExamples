add_example(SegmentWithGeodesicActiveContourLevelSet)

compare_to_baseline(
    EXAMPLE_NAME SegmentWithGeodesicActiveContourLevelSet
    TEST_NAME GeodesicActiveContourLeftVentricleTestBaselineComparison
    BASELINE_PREFIX OutputBaseline1
    DEPENDS GeodesicActiveContourLeftVentricleTest
    TEST_IMAGE Output1.png)
compare_to_baseline(
    EXAMPLE_NAME SegmentWithGeodesicActiveContourLevelSet
    TEST_NAME GeodesicActiveContourRightVentricleTestBaselineComparison
    BASELINE_PREFIX OutputBaseline2
    DEPENDS GeodesicActiveContourRightVentricleTest
    TEST_IMAGE Output2.png)
compare_to_baseline(
    EXAMPLE_NAME SegmentWithGeodesicActiveContourLevelSet
    TEST_NAME GeodesicActiveContourWhiteMatterTestBaselineComparison
    BASELINE_PREFIX OutputBaseline3
    DEPENDS GeodesicActiveContourWhiteMatterTest
    TEST_IMAGE Output3.png)
compare_to_baseline(
    EXAMPLE_NAME SegmentWithGeodesicActiveContourLevelSet
    TEST_NAME GeodesicActiveContourGrayMatterTestBaselineComparison
    BASELINE_PREFIX OutputBaseline4
    DEPENDS GeodesicActiveContourGrayMatterTest
    TEST_IMAGE Output4.png)

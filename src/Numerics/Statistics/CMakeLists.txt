add_example( ComputeHistogramFromGrayscaleImage )
add_example(HistogramCreationAndBinAccess)

add_example(CreateGaussianDistribution)
compare_to_baseline(EXAMPLE_NAME CreateGaussianDistribution
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateHistogramFromListOfMeasurements)
compare_to_baseline(EXAMPLE_NAME CreateHistogramFromListOfMeasurements
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateListOfSampleMeasurements)
compare_to_baseline(EXAMPLE_NAME CreateListOfSampleMeasurements
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateListOfSamplesFromImageWithoutDuplication)
compare_to_baseline(EXAMPLE_NAME CreateListOfSamplesFromImageWithoutDuplication
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateListOfSamplesWithIDs)
compare_to_baseline(EXAMPLE_NAME CreateListOfSamplesWithIDs
  BASELINE_PREFIX OutputBaseline
  )

add_example(2DGaussianMixtureModelExpectMax)
compare_to_baseline(EXAMPLE_NAME 2DGaussianMixtureModelExpectMax
  BASELINE_PREFIX OutputBaseline
  )

add_example(SpatialSearch)
compare_to_baseline(EXAMPLE_NAME SpatialSearch
  BASELINE_PREFIX OutputBaseline
  )

add_example(DistributionOfPixelsUsingGMM)
compare_to_baseline(EXAMPLE_NAME DistributionOfPixelsUsingGMM
  BASELINE_PREFIX OutputBaseline
  )

add_example(DistributeSamplingUsingGMM)
compare_to_baseline(EXAMPLE_NAME DistributeSamplingUsingGMM
  BASELINE_PREFIX OutputBaseline
  )

add_example(ComputeTextureFeatures)
compare_to_baseline(EXAMPLE_NAME ComputeTextureFeatures
  BASELINE_PREFIX OutputBaseline
  )

#TODO: Need to fix build errors ComputeHistogramOfMaskedRegion
#add_example(ComputeHistogramOfMaskedRegion)
#compare_to_baseline(EXAMPLE_NAME ComputeHistogramOfMaskedRegion
#  BASELINE_PREFIX OutputBaseline
#  )

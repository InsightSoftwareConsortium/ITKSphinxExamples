add_example( ComputeHistogramFromGrayscaleImage )
add_example(HistogramCreationAndBinAccess)

add_example(CreateGaussianDistribution)
add_example(CreateHistogramFromListOfMeasurements)
add_example(CreateListOfSampleMeasurements)
add_example(CreateListOfSamplesFromImageWithoutDuplication)
add_example(CreateListOfSamplesWithIDs)
add_example(2DGaussianMixtureModelExpectMax)
add_example(SpatialSearch)

# TODO: Examples need to fix build error
# add_example(DistributionOfPixelsUsingGMM)
#compare_to_baseline(EXAMPLE_NAME DistributionOfPixelsUsingGMM
#  BASELINE_PREFIX OutputBaseline
#  )

#add_example(DistributeSamplingUsingGMM)
#compare_to_baseline(EXAMPLE_NAME DistributeSamplingUsingGMM
#  BASELINE_PREFIX OutputBaseline
#  )
#=======================================

# TODO: Examples need correct results
add_example(ComputeTextureFeatures)
#compare_to_baseline(EXAMPLE_NAME ComputeTextureFeatures
#  BASELINE_PREFIX OutputBaseline
#  )
#=======================================

#TODO: Need to fix build errors ComputeHistogramOfMaskedRegion
#add_example(ComputeHistogramOfMaskedRegion)
#compare_to_baseline(EXAMPLE_NAME ComputeHistogramOfMaskedRegion
#  BASELINE_PREFIX OutputBaseline
#  )

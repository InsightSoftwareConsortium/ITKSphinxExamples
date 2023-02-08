add_example(CreateACovariantVector)
add_example(CreateAPointSet)
add_example(DoDataParallelThreading)
add_example(CovariantVectorNorm)
add_example(CovariantVectorDotProduct)
add_example(VectorDotProduct)
add_example(GetTypeBasicInformation)
add_example(DistanceBetweenPoints)
add_example(DistanceBetweenIndices)
add_example(CreateAVector)
add_example(TryCatchException)
add_example(BoundingBoxOfAPointSet)
add_example(MersenneTwisterRandomIntegerGenerator)
add_example(MersenneTwisterRandomNumberGenerator)
add_example(ObserveAnEvent)
add_example(ComputeTimeBetweenPoints)
add_example(WatchAFilter)
add_example(IterateOnAVectorContainer)
add_example(CreateAnotherInstanceOfAFilter)
add_example(CreateAFixedArray)
add_example(AddOffsetToIndex)
add_example(GetNameOfClass)
add_example(CreateAnImageRegion)
add_example(IsPixelInsideRegion)
add_example(ImageBufferAndIndexRange)
add_example(ImageRegionIntersection)

add_example(ImageRegionOverlap)
compare_to_baseline(
  EXAMPLE_NAME ImageRegionOverlap
  BASELINE_PREFIX OutputBaseline
)

add_example(CreateAIndex)
add_example(CreateASize)
add_example(GetImageSize)
add_example(CreateAnRGBImage)

add_example(SetPixelValueInOneImage)
compare_to_baseline(
  EXAMPLE_NAME SetPixelValueInOneImage
  BASELINE_PREFIX OutputBaseline
)

add_example(DuplicateAnImage)
add_example(ApplyAFilterOnlyToASpecifiedRegionOfAnImage)
add_example(IterateOverARegionWithAShapedNeighborhoodIterator)
add_example(IterateOverARegionWithAShapedNeighborhoodIteratorManual)
add_example(GenerateOffsetsShapedImageNeighborhood)
add_example(CreateABackwardDifferenceOperator)
add_example(BuildAHelloWorldProgram)
add_example(TraceMemoryBetweenPoints)
add_example(StreamAPipeline)

# ConceptChecking
add_example(ConceptCheckingIsFloatingPoint)
add_example(ConceptCheckingIsSameType)
add_example(ConceptCheckingIsSameDimension)

add_example(ReRunPipelineWithChangingLargestPossibleRegion)
add_example(CreateAnImageOfVectors)
add_example(ReadWriteVectorImage)
compare_to_baseline(EXAMPLE_NAME ReadWriteVectorImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateAnImage)

add_example(ImportPixelBufferIntoAnImage)
compare_to_baseline(EXAMPLE_NAME ImportPixelBufferIntoAnImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(FilterAndParallelizeImageRegion)
add_example(UseParallelizeImageRegion)
add_example(PiConstant)
add_example(Matrix)
add_example(MatrixInverse)
add_example(VariableLengthVector)
add_example(BresenhamLine)
add_example(MakePartOfImageTransparent)
compare_to_baseline(EXAMPLE_NAME MakePartOfImageTransparent
  BASELINE_PREFIX MakePartOfImageTransparent
  )

add_example(ConvertArrayToImage)
compare_to_baseline(EXAMPLE_NAME ConvertArrayToImage
  BASELINE_PREFIX ConvertArrayToImageOutput
  )

add_example(CropImageBySpecifyingRegion)
add_example(ApplyCustomOperationToEachPixelInImage)
add_example(CreateVectorImage)
add_example(NeighborhoodIteratorOnVectorImage)
add_example(IterateOverSpecificRegion)
add_example(RandomSelectOfPixelsFromRegion)
add_example(RandomSelectPixelFromRegionWithoutReplacee)

add_example(IterateLineThroughImage)

compare_to_baseline(EXAMPLE_NAME IterateLineThroughImage
  BASELINE_PREFIX IterateLineThroughImage
  )

add_example(IterateLineThroughImageWithoutWriteAccess)
add_example(IterateWithNeighborhoodWithoutAccess)
add_example(IterateRegionWithoutWriteAccess)

add_example(IterateRegionWithAccessToIndexWithWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithAccessToIndexWithWriteAccess
  BASELINE_PREFIX IterateRegionWithAccessToIndexWithWriteAccess
  )

add_example(IterateRegionWithAccessToIndexWithoutWriteAccess)

add_example(CreateGaussianKernel)
add_example(CreateGaussianDerivativeKernel)
add_example(CreateLaplacianKernel)
add_example(CreateDerivativeKernel)
add_example(CreateSobelKernel)
add_example(CreateForwardDifferenceKernel)

add_example(AddNoiseToBinaryImage)
compare_to_baseline(EXAMPLE_NAME AddNoiseToBinaryImage
  BASELINE_PREFIX AddNoiseToBinaryImage
  )

add_example(SortITKIndex)
add_example(ReturnObjectFromFunction)
add_example(CreateAnotherInstanceOfAnImage)
add_example(PassImageToFunction)
add_example(DeepCopyImage)
add_example(PermuteSequenceOfIndices)

#==================================================
# TODO: Complete these examples
add_example(ThrowException)
#add_example(FilterImageUsingMultipleThreads)
#add_example(CastVectorImageToAnotherType)
#add_example(MultipleInputsOfDifferentType)
#add_example(MultipleOutputsOfDifferentType)
#add_example(GetOrSetMemberVariableOfITKClass)
#add_example(DemonstrateAllOperators)
#==================================================

# TODO: Not valid code
#add_example(ProduceImageProgrammatically)
#compare_to_baseline(EXAMPLE_NAME ProduceImageProgrammatically
#  BASELINE_PREFIX OutputBaseline
#  )
#==================================================

add_example(FilterImage)
add_example(FilterImageWithoutCopying)
add_example(MultipleInputsOfSameType)

add_example(MultipleOutputsOfSameType)
compare_to_baseline(EXAMPLE_NAME MultipleOutputsOfSameType
  BASELINE_PREFIX TestOutput1 TestOutput2
  )

add_example(MiniPipeline)
compare_to_baseline(EXAMPLE_NAME MiniPipeline
  BASELINE_PREFIX MiniPipelineOutput
  )

add_example(IterateImageStartingAtSeed)
add_example(StoreNonPixelDataInImage)
add_example(CheckIfModuleIsPresent)

add_example(DisplayImage)
compare_to_baseline(EXAMPLE_NAME DisplayImage
  BASELINE_PREFIX DisplayImage
  )

add_example(DirectWarningToFile)

# TODO: complete example
add_example(MultiThreadOilPainting)
#==================================================

if(VTK_DIR)
add_example(FindMaxAndMinInImage)
compare_to_baseline(EXAMPLE_NAME FindMaxAndMinInImage
  BASELINE_PREFIX FindMaxAndMinInImageOutput
  )

add_example(InPlaceFilterOfImage)
#TODO: Make example save output image, and then compare it to a baseline
#compare_to_baseline(EXAMPLE_NAME InPlaceFilterOfImage
#  BASELINE_PREFIX OutputBaseline
#  )

add_example(IterateRegionWithNeighborhood)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithNeighborhood
  BASELINE_PREFIX IterateRegionWithWriteAccess
  )

add_example(IterateRegionWithWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithWriteAccess
  BASELINE_PREFIX IterateRegionWithWriteAccess
  )

add_example(MakeOutOfBoundsPixelsReturnConstValue)
compare_to_baseline(EXAMPLE_NAME MakeOutOfBoundsPixelsReturnConstValue
  BASELINE_PREFIX MakeOutOfBoundsPixelsReturnConstValue
  )
endif()

add_example(SetDefaultNumberOfThreads)
add_example(EagerModuleLoadingPython)

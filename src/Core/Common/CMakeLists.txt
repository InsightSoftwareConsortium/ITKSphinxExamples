add_example( CreateACovariantVector )
add_example( CreateAPointSet )
add_example( DoDataParallelThreading )
add_example( CovariantVectorNorm )
add_example( CovariantVectorDotProduct )
add_example( VectorDotProduct )
add_example( GetTypeBasicInformation )
add_example( DistanceBetweenPoints )
add_example( DistanceBetweenIndices )
add_example( CreateAVector )
add_example( TryCatchException )
add_example( BoundingBoxOfAPointSet )
add_example( MersenneTwisterRandomIntegerGenerator )
add_example( MersenneTwisterRandomNumberGenerator )
add_example( ObserveAnEvent )
add_example( ComputeTimeBetweenPoints )
add_example( WatchAFilter )
add_example( IterateOnAVectorContainer )
add_example( CreateAnother )
add_example( CreateAFixedArray )
add_example( AddOffsetToIndex )
add_example( GetNameOfClass )
add_example( CreateAnImageRegion )
add_example( IsPixelInsideRegion )
add_example( ImageRegionIntersection )

add_example( ImageRegionOverlap )
compare_to_baseline(
  EXAMPLE_NAME ImageRegionOverlap
  BASELINE_PREFIX OutputBaseline
)

add_example( CreateAIndex )
add_example( CreateASize )
add_example( GetImageSize )
add_example( CreateAnRGBImage )

add_example( SetPixelValueInOneImage )
compare_to_baseline(
  EXAMPLE_NAME SetPixelValueInOneImage
  BASELINE_PREFIX OutputBaseline
)

add_example( DuplicateAnImage )
add_example( ApplyAFilterOnlyToASpecifiedRegionOfAnImage )
add_example( IterateOverARegionWithAShapedNeighborhoodIterator )
add_example( IterateOverARegionWithAShapedNeighborhoodIteratorManual )
add_example( CreateABackwardDifferenceOperator )
add_example( BuildAHelloWorldProgram )
add_example( TraceMemoryBetweenPoints )
add_example( StreamAPipeline )

# ConceptChecking
add_example( ConceptCheckingIsFloatingPoint )
add_example( ConceptCheckingIsSameType )
add_example( ConceptCheckingIsSameDimension )

add_example( ReRunPipelineWithChangingLargestPossibleRegion )
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
compare_to_baseline(EXAMPLE_NAME PiConstant
  BASELINE_PREFIX OutputBaseline
  )

add_example(Matrix)
compare_to_baseline(EXAMPLE_NAME Matrix
  BASELINE_PREFIX OutputBaseline
  )

add_example(MatrixInverse)
compare_to_baseline(EXAMPLE_NAME MatrixInverse
  BASELINE_PREFIX OutputBaseline
  )

add_example(VariableLengthVector)
compare_to_baseline(EXAMPLE_NAME VariableLengthVector
  BASELINE_PREFIX OutputBaseline
  )

add_example(BresenhamLine)
compare_to_baseline(EXAMPLE_NAME BresenhamLine
  BASELINE_PREFIX OutputBaseline
  )

add_example(Transparency)
compare_to_baseline(EXAMPLE_NAME Transparency
  BASELINE_PREFIX OutputBaseline
  )

add_example(ConvertArrayToImage)
compare_to_baseline(EXAMPLE_NAME ConvertArrayToImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CropImageBySpecifyingRegion)
compare_to_baseline(EXAMPLE_NAME CropImageBySpecifyingRegion
  BASELINE_PREFIX OutputBaseline
  )

add_example(CustomOperationToEachPixelInImage)
compare_to_baseline(EXAMPLE_NAME CustomOperationToEachPixelInImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(FindMaxAndMinInImage)
compare_to_baseline(EXAMPLE_NAME FindMaxAndMinInImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateVectorImage)
compare_to_baseline(EXAMPLE_NAME CreateVectorImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(NeighborhoodIteratorOnVectorImage)
compare_to_baseline(EXAMPLE_NAME NeighborhoodIteratorOnVectorImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CastVectorImageToAnotherType)
compare_to_baseline(EXAMPLE_NAME CastVectorImageToAnotherType
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateOverSpecificRegion)
compare_to_baseline(EXAMPLE_NAME IterateOverSpecificRegion
  BASELINE_PREFIX OutputBaseline
  )

add_example(RandomSelectOfPixelsFromRegion)
compare_to_baseline(EXAMPLE_NAME RandomSelectOfPixelsFromRegion
  BASELINE_PREFIX OutputBaseline
  )

add_example(RandomSelectPixelFromRegionWithoutReplacee)
compare_to_baseline(EXAMPLE_NAME RandomSelectPixelFromRegionWithoutReplacee
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateLineThroughImage)
compare_to_baseline(EXAMPLE_NAME IterateLineThroughImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateLineThroughImageWithoutWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateLineThroughImageWithoutWriteAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateRegionWithNeighborhood)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithNeighborhood
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateWithNeighborhoodWithoutAccess)
compare_to_baseline(EXAMPLE_NAME IterateWithNeighborhoodWithoutAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateRegionWithWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithWriteAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateRegionWithoutWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithoutWriteAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(OutOfBoundsPixelsReturnConstValue)
compare_to_baseline(EXAMPLE_NAME OutOfBoundsPixelsReturnConstValue
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateRegionWithAccessToIndexWithWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithAccessToIndexWithWriteAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateRegionWithAccessToIndexWithoutWriteAccess)
compare_to_baseline(EXAMPLE_NAME IterateRegionWithAccessToIndexWithoutWriteAccess
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateGaussianKernel)
compare_to_baseline(EXAMPLE_NAME CreateGaussianKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateGaussianDerivativeKernel)
compare_to_baseline(EXAMPLE_NAME CreateGaussianDerivativeKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateLaplacianKernel)
compare_to_baseline(EXAMPLE_NAME CreateLaplacianKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateDerivativeKernel)
compare_to_baseline(EXAMPLE_NAME CreateDerivativeKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateSobelKernel)
compare_to_baseline(EXAMPLE_NAME CreateSobelKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateForwardDifferenceKernel)
compare_to_baseline(EXAMPLE_NAME CreateForwardDifferenceKernel
  BASELINE_PREFIX OutputBaseline
  )

add_example(AddNoiseToBinaryImage)
compare_to_baseline(EXAMPLE_NAME AddNoiseToBinaryImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(SortITKIndex)
compare_to_baseline(EXAMPLE_NAME SortITKIndex
  BASELINE_PREFIX OutputBaseline
  )

add_example(ReturnObjectFromFunction)
compare_to_baseline(EXAMPLE_NAME ReturnObjectFromFunction
  BASELINE_PREFIX OutputBaseline
  )

add_example(CreateAnotherInstanceOfAnImage)
compare_to_baseline(EXAMPLE_NAME CreateAnotherInstanceOfAnImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(PassImageToFunction)
compare_to_baseline(EXAMPLE_NAME PassImageToFunction
  BASELINE_PREFIX OutputBaseline
  )

add_example(DeepCopyImage)
compare_to_baseline(EXAMPLE_NAME DeepCopyImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(PermuteSequenceOfIndices)
compare_to_baseline(EXAMPLE_NAME PermuteSequenceOfIndices
  BASELINE_PREFIX OutputBaseline
  )

#==================================================
# TODO: Complete these examples
add_example(ThrowException)
compare_to_baseline(EXAMPLE_NAME ThrowException
  BASELINE_PREFIX OutputBaseline
  )

# TODO: Not valid code
#add_example(ProduceImageProgrammatically)
#compare_to_baseline(EXAMPLE_NAME ProduceImageProgrammatically
#  BASELINE_PREFIX OutputBaseline
#  )

add_example(FilterImage)
compare_to_baseline(EXAMPLE_NAME FilterImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(FilterImageWithoutCopying)
compare_to_baseline(EXAMPLE_NAME FilterImageWithoutCopying
  BASELINE_PREFIX OutputBaseline
  )

add_example(FilterImageUsingMultipleThreads)
compare_to_baseline(EXAMPLE_NAME FilterImageUsingMultipleThreads
  BASELINE_PREFIX OutputBaseline
  )

add_example(MultiThreadOilPainting)
compare_to_baseline(EXAMPLE_NAME MultiThreadOilPainting
  BASELINE_PREFIX OutputBaseline
  )

add_example(MultipleInputsOfSameType)
compare_to_baseline(EXAMPLE_NAME MultipleInputsOfSameType
  BASELINE_PREFIX OutputBaseline
  )

add_example(MultipleInputsOfDifferentType)
compare_to_baseline(EXAMPLE_NAME MultipleInputsOfDifferentType
  BASELINE_PREFIX OutputBaseline
  )

add_example(MultipleOutputsOfSameType)
compare_to_baseline(EXAMPLE_NAME MultipleOutputsOfSameType
  BASELINE_PREFIX OutputBaseline
  )

add_example(MultipleOutputsOfDifferentType)
compare_to_baseline(EXAMPLE_NAME MultipleOutputsOfDifferentType
  BASELINE_PREFIX OutputBaseline
  )

add_example(GetOrSetMemberVariableOfITKClass)
compare_to_baseline(EXAMPLE_NAME GetOrSetMemberVariableOfITKClass
  BASELINE_PREFIX OutputBaseline
  )

add_example(MiniPipeline)
compare_to_baseline(EXAMPLE_NAME MiniPipeline
  BASELINE_PREFIX OutputBaseline
  )

add_example(IterateImageStartingAtSeed)
compare_to_baseline(EXAMPLE_NAME IterateImageStartingAtSeed
  BASELINE_PREFIX OutputBaseline
  )

add_example(InPlaceFilterOfImage)
compare_to_baseline(EXAMPLE_NAME InPlaceFilterOfImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(DemonstrateAllOperators)
compare_to_baseline(EXAMPLE_NAME DemonstrateAllOperators
        BASELINE_PREFIX OutputBaseline
        )
add_example(StoreNonPixelDataInImage)
compare_to_baseline(EXAMPLE_NAME StoreNonPixelDataInImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(CheckIfModuleIsPresent)
compare_to_baseline(EXAMPLE_NAME CheckIfModuleIsPresent
  BASELINE_PREFIX OutputBaseline
  )

add_example(DisplayImage)
compare_to_baseline(EXAMPLE_NAME DisplayImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(DirectWarningToFile)
compare_to_baseline(EXAMPLE_NAME DirectWarningToFile
        BASELINE_PREFIX OutputBaseline
        )
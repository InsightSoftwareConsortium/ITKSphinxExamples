add_example( CreateACovariantVector )
add_example( CreateAPointSet )
add_example( DoDataParallelThreading )
add_example( CovariantVectorNorm )
add_example( CovariantVectorDotProduct )
add_example( GetTypeBasicInformation )
add_example( DistanceBetweenPoints )
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
add_example( CreateAImageRegion )
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
add_example( CreateABackwardDifferenceOperator )
add_example( BuildAHelloWorldProgram )
add_example( TraceMemoryBetweenPoints )
add_example( StreamAPipeline )

# ConceptChecking
add_example( ConceptCheckingIsFloatingPoint )
add_example( ConceptCheckingIsSameType )
add_example( ConceptCheckingIsSameDimension )

add_example( ReRunPipelineWithChangingLargestPossibleRegion )

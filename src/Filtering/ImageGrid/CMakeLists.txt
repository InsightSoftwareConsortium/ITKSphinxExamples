add_example( ChangeImageOriginSpacingOrDirection )

add_example( FlipAnImageOverSpecifiedAxes )
compare_to_baseline(
  EXAMPLE_NAME FlipAnImageOverSpecifiedAxes
  BASELINE_PREFIX OutputBaseline
)

add_example( PadAnImageWithAConstant )
compare_to_baseline(
  EXAMPLE_NAME PadAnImageWithAConstant
  BASELINE_PREFIX OutputBaseline
)

add_example( PadAnImageByMirroring )
compare_to_baseline(
  EXAMPLE_NAME PadAnImageByMirroring
  BASELINE_PREFIX OutputBaseline
)

add_example( Create3DVolume )
# There is currently an issue with the TileImageFilter SetDefaultPixelValue in
# the Python wrapping. See https://issues.itk.org/jira/browse/ITK-3422
#compare_to_baseline(
  #EXAMPLE_NAME Create3DVolume
  #BASELINE_PREFIX OutputBaseline
#)

add_example( AppendTwo3DVolumes )
compare_to_baseline(
  EXAMPLE_NAME AppendTwo3DVolumes
  BASELINE_PREFIX OutputBaseline
)

add_example( ResampleAnImage )
compare_to_baseline(
  EXAMPLE_NAME ResampleAnImage
  BASELINE_PREFIX OutputBaseline
)

add_example( UpsampleOrDownsampleScalarImage )
compare_to_baseline(
  EXAMPLE_NAME UpsampleOrDownsampleScalarImage
  BASELINE_PREFIX OutputBaseline
)

add_example( PasteImageIntoAnotherOne )
compare_to_baseline(
  EXAMPLE_NAME PasteImageIntoAnotherOne
  BASELINE_PREFIX OutputBaseline
)

add_example( PermuteAxesOfAnImage )
compare_to_baseline(
  EXAMPLE_NAME PermuteAxesOfAnImage
  BASELINE_PREFIX OutputBaseline
)

add_example( ResampleAVectorImage )
compare_to_baseline(
  EXAMPLE_NAME ResampleAVectorImage
  BASELINE_PREFIX OutputBaseline )

add_example( ExtractRegionOfInterestInOneImage )
compare_to_baseline( EXAMPLE_NAME ExtractRegionOfInterestInOneImage BASELINE_PREFIX OutputBaseline )

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
compare_to_baseline(
  EXAMPLE_NAME Create3DVolume
  BASELINE_PREFIX OutputBaseline
)

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

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

add_example( UpsampleAnImage )
compare_to_baseline(
  EXAMPLE_NAME UpsampleAnImage
  BASELINE_PREFIX BrainProtonDensitySlice
)

add_example( ResampleAScalarImage )
compare_to_baseline(
  EXAMPLE_NAME ResampleAScalarImage
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

add_example(WarpAnImageUsingADeformationField)
compare_to_baseline(EXAMPLE_NAME WarpAnImageUsingADeformationField
  BASELINE_PREFIX OutputBaseline
  )

add_example(ProcessA2DSliceOfA3DImage)
compare_to_baseline(EXAMPLE_NAME ProcessA2DSliceOfA3DImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(PadImageByWrapping)
compare_to_baseline(EXAMPLE_NAME PadImageByWrapping
  BASELINE_PREFIX image
  )

add_example(ShrinkImage)

add_example(TileImagesSideBySide)

add_example(FitSplineIntoPointSet)

#TODO: Uncomment when valid input is added to example
#add_example(Stack2DImagesInto3DImage)
#compare_to_baseline(EXAMPLE_NAME ProcessA2DSliceOfA3DImage
#  BASELINE_PREFIX OutputBaseline
#  )

add_example(RunImageFilterOnRegionOfImage)
compare_to_baseline(EXAMPLE_NAME RunImageFilterOnRegionOfImage
        BASELINE_PREFIX RunImageFilterOnRegionOfImage
        )

add_example(CropImageBySpecifyingRegion2)
compare_to_baseline(EXAMPLE_NAME CropImageBySpecifyingRegion2
        BASELINE_PREFIX CropImageBySpecifyingRegion2
        )

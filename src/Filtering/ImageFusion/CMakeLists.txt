
add_example( OverlayLabelMapOnTopOfAnImage )
compare_to_baseline( EXAMPLE_NAME OverlayLabelMapOnTopOfAnImage BASELINE_PREFIX OutputBaseline )

add_example(ColorLabeledRegions)
compare_to_baseline(EXAMPLE_NAME ColorLabeledRegions
  BASELINE_PREFIX output
  )

add_example(ColorBoundariesOfRegions)
compare_to_baseline(EXAMPLE_NAME ColorBoundariesOfRegions
  BASELINE_PREFIX output
  )

add_example(OverlayLabelMapOnImage)
compare_to_baseline(EXAMPLE_NAME OverlayLabelMapOnImage
  BASELINE_PREFIX output
  )

add_example( DilateABinaryImage )
compare_to_baseline(
  EXAMPLE_NAME DilateABinaryImage
  BASELINE_PREFIX OutputBaseline
)

add_example( ErodeABinaryImage )
compare_to_baseline(
  EXAMPLE_NAME ErodeABinaryImage
  BASELINE_PREFIX OutputBaseline
)

add_example(ThinImage)
compare_to_baseline(EXAMPLE_NAME ThinImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(PruneBinaryImage)
compare_to_baseline(EXAMPLE_NAME PruneBinaryImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(OpeningBinaryImage)
compare_to_baseline(EXAMPLE_NAME OpeningBinaryImage
  BASELINE_PREFIX OutputBaseline
  )

add_example(ClosingBinaryImage)
compare_to_baseline(EXAMPLE_NAME ClosingBinaryImage
  BASELINE_PREFIX OutputBaseline
  )
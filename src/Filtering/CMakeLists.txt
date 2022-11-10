set(Filtering_MODULES
  AnisotropicSmoothing
  AntiAlias
  BinaryMathematicalMorphology
  Colormap
  Convolution
  CurvatureFlow
  DistanceMap
  FastMarching
  FFT
  ImageCompare
  ImageCompose
  ImageFeature
  ImageFilterBase
  ImageFusion
  ImageGradient
  ImageGrid
  ImageIntensity
  ImageLabel
  ImageStatistics
  LabelMap
  MathematicalMorphology
  Path
  QuadEdgeMeshFiltering
  Smoothing
  Thresholding
)

set(Filtering_MODULES_IGNORED
  # TODO: Fix ImageGradient examples and re-enable
  ImageGradient
)

foreach(_module ${Filtering_MODULES})
  if(NOT (${_module} IN_LIST Filtering_MODULES_IGNORED))
    add_subdirectory_if_module_enabled(${_module})
  endif()
  add_module_archives(${_module})
endforeach()

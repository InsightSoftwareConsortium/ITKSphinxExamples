---
name: SegmentWithGeodesicActiveContourLevelSet
---

# Segment With Geodesic Active Contour Level Set

```{index} single: GeodesicActiveContourLevelSetImageFilter single: CurvatureAnisotropicDiffusionImageFilter single: GradientMagnitudeRecursiveGaussianImageFilter single: SigmoidImageFilter single: FastMarchingImageFilter single: RescaleIntensityImageFilter single: BinaryThresholdImageFilter
```

## Synopsis

Segments structures in images based on a user supplied edge potential map.

This example is the same as the one in the ITK software guide. It was re-organized and
does not contain any comments about the executed filters. Please refer to the guide
for more details.

## Results

:::{figure} BrainProtonDensitySlice.png
:alt: Input image
:scale: 50%

Input image
:::

:::{only} html
```{image} Evolution.gif
:alt: Evolution of the segmentation depending on the number of iterations (10 to 500).
:scale: 50%
```
:::

Used parameters:

- Left ventricle: 81 114 5.0 1.0 -0.5 3.0 2.0
- Right ventricle: 99 114 5.0 1.0 -0.5 3.0 2.0
- White matter: 56 92 5.0 1.0 -0.3 2.0 10.0
- Gray matter: 40 90 5.0 .5 -0.3 2.0 10.0

## Code

### Python

```{literalinclude} Code.py
:language: python
:lines: 1, 16-
```

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::GeodesicActiveContourLevelSetImageFilter
```

---
name: SegmentBloodVessels
---

# Segment Blood Vessels

```{index} single: Hessian3DToVesselnessMeasureImageFilter pair: segment; vessel pair: segment; tube
```

## Synopsis

The example takes an image (say MRA image), computes the vesselness measure
of the image using the HessianRecursiveGaussianImageFilter and the
Hessian3DToVesselnessMeasureImageFilter. The goal is to detect bright, tubular
structures in the image.

Note that since the algorithm is based on the [Hessian], it will also identify
black tubular structures.

An important parameter is the `Sigma` that determines the amount of smoothing
applied during Hessian estimation.  A larger `Sigma` will decrease the
identification of noise or small structures as vessels.  In this example, the
`Sigma` is large enough only vessels comprising the [Circle of Willis] and
other large vessels are segmented.

## Results

:::{figure} Input.png
:alt: Input image
:scale: 70%

Input head MRA.
:::

:::{figure} Output.png
:alt: Output image
:scale: 70%

Output vessel segmentation.
:::

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
.. breathelink:: itk::Hessian3DToVesselnessMeasureImageFilter
```

```{eval-rst}
.. breathelink:: itk::HessianRecursiveGaussianImageFilter
```

[circle of willis]: https://en.wikipedia.org/wiki/Circle_of_Willis
[hessian]: https://en.wikipedia.org/wiki/Hessian_matrix

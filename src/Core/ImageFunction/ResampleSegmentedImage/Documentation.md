---
name: ResampleSegmentedImage
---

# Resample Segmented Image

```{index} single: LabelImageGaussianInterpolateImageFunction pair: segmented; image
```

## Synopsis

Resample (stretch or compress) a label image resulting form segmentation.

For more on why label image interpolation is necessary and how it works, see the [associated Insight Journal article](https://www.insight-journal.org/browse/publication/705).

## Results

:::{figure} 2th_cthead1.png
:alt: Input label image.
:scale: 50%

Input label image
:::

:::{figure} OutputBaseline.png
:alt: QuickView output.
:scale: 50%

Resample with label image gaussian interpolation.
:::

:::{figure} OutputNearestBaseline.png
:alt: QuickView output.
:scale: 50%

Resample with nearest neighbor interpolation.
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
.. breathelink:: itk::LabelImageGaussianInterpolateImageFunction
```

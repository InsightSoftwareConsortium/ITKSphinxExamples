---
name: ComputerMagInVectorImageToMakeMagImage
---

# Computer Magnitude in Vector Image to Make Magnitude Image

```{index} single: VectorMagnitudeImageFilter pair: magnitude; image pair: vector; image
```

## Synopsis

Compute the magnitude of each pixel in a vector image to produce a magnitude image

## Results

:::{figure} Yinyang.png
:alt: Yinyang.png
:scale: 70%

Yinyang.png
:::

:::{figure} ComputerMagInVectorImageToMakeMagImage.png
:alt: output.png
:scale: 70%

output.png
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::VectorMagnitudeImageFilter
```

---
name: SobelEdgeDetectionImageFilter
---

# Sobel Edge Detection Image Filter

```{index} single: SobelEdgeDetectionImageFilter
```

## Synopsis

Apply SobelEdgeDetectionImageFilter to an image

## Results

:::{figure} Gourds.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} SobelEdgeDetectionImageFilterRescaledOutputBaseline.png
:alt: Rescaled Output image
:scale: 50%

Rescaled Output image (values are in \[0, 255\])
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
.. breathelink:: itk::SobelEdgeDetectionImageFilter
```

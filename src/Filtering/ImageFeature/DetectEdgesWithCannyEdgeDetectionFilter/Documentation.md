---
name: DetectEdgesWithCannyEdgeDetectionFilter
---

# Detect Edges With Canny Edge Detection Filter

```{index} single: CannyEdgeDetectionImageFilter
```

## Synopsis

Apply CannyEdgeDetectionImageFilter to an image

## Results

:::{figure} cthead1.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} OutputBaseline.png
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
.. breathelink:: itk::CannyEdgeDetectionImageFilter
```

---
name: ApplyAColormapToAnImage
---

# Apply a Color Map to an Image

```{index} single: ScalarToRGBColormapImageFilter
```

## Synopsis

Apply a color map to an image

## Results

:::{figure} Gourds.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} OutputBaseline.png
:alt: Output image
:scale: 50%

Output image
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
.. breathelink:: itk::ScalarToRGBColormapImageFilter
```

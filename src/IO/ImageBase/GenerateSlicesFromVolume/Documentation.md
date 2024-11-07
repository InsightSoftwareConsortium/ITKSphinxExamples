---
name: GenerateSlicesFromVolume
---

# Generate Slices From Volume

```{index} single: ImageSeriesWriter single: NumericSeriesFileNames
```

## Synopsis

Create series of 2D images from a given volume.

## Results

:::{figure} Input.png
:alt: Input image
:scale: 50%

Input image
:::

:::{figure} Output-20Baseline.png
:alt: Output image, slice 20
:scale: 200%

Output image, slice 20
:::

:::{figure} Output-30Baseline.png
:alt: Output image, slice 30
:scale: 200%

Output image, slice 30
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

```{literalinclude} Code.py
:language: python
:lines: 1, 17-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::NumericSeriesFileNames
```

```{eval-rst}
.. breathelink:: itk::ImageSeriesWriter
```

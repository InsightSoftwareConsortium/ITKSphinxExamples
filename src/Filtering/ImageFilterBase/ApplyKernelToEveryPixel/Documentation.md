---
name: ApplyKernelToEveryPixel
---

# Apply Kernel to Every Pixel

```{index} single: NeighborhoodOperatorImageFilter pair: kernel; pixel
```

## Synopsis

Apply a kernel to every pixel in an image.

## Results

:::{figure} input.png
:alt: input.png
:scale: 70%

input.png
:::

:::{figure} output.png
:alt: output.png
:scale: 70%

output.png
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
.. breathelink:: itk::NeighborhoodOperatorImageFilter
```

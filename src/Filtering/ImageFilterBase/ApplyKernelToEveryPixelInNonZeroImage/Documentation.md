---
name: ApplyKernelToEveryPixelInNonZeroImage
---

# Apply Kernel to Every Pixel in Non-Zero Image

```{index} single: MaskNeighborhoodOperatorImageFilter pair: mask; non-zero single: kernel
```

## Synopsis

Apply a kernel to every pixel in an image that is non-zero in a mask.

## Results

:::{figure} input.png
:alt: input.png
:scale: 70%

input.png
:::

:::{figure} mask.png
:alt: mask.png
:scale: 70%

mask.png
:::

:::{figure} output.png
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
.. breathelink:: itk::MaskNeighborhoodOperatorImageFilter
```

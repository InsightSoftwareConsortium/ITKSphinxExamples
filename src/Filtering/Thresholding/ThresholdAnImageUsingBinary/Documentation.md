---
name: ThresholdAnImageUsingBinary
---

# Threshold an Image Using Binary Thresholding

```{index} single: BinaryThresholdImageFilter
```

## Synopsis

Binarize an input image by thresholding.

## Results

:::{figure} cthead1.png
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
.. breathelink:: itk::BinaryThresholdImageFilter
```

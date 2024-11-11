---
name: UseParallelizeImageRegion
---

# Use ParallelizeImageRegion

```{index} single: MultiThreaderBase
```

## Synopsis

This example demonstrates how to use MultiThreaderBase::ParallelizeImageRegion
to apply a non-trivial operation for all pixels in an image, in parallel.  To
perform a multi-threaded operation like this prior ITK 5.0 required the
creation of a  class.

## Results

:::{figure} CellsFluorescence1.png
:alt: Segmentation and custom colorization.
:scale: 100%

Segmentation and custom colorization of an image using
MultiThreaderBase::ParallelizeImageRegion.
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MultiThreaderBase
```

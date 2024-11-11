---
name: ApplyAccumulateImageFilter
---

# Apply Accumulate Image Filter

```{index} single: AccumulateImageFilter
```

## Synopsis

Accumulate pixels of an image along a selected direction.

## Results

:::{figure} Input.png
:alt: Input image
:scale: 100%

Input image
:::

:::{figure} Output0.png
:alt: Output image 0
:scale: 100%

Output image accumulated along direction 0
:::

:::{figure} Output1.png
:alt: Output image 1
:scale: 100%

Output image accumulated along direction 1
:::

:::{figure} Output2.png
:alt: Output image 2
:scale: 100%

Output image accumulated along direction 2
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::AccumulateImageFilter
```

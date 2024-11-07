---
name: MorphologicalWatershedSegmentation
---

# Morphological Watershed Segmentation

```{index} single: MorphologicalWatershedImageFilter single: watershed
```

## Synopsis

Morphological watershed segmentation.

## Results

:::{figure} input.png
:alt: input.png
:scale: 70%

input.png
:::

:::{figure} output_20_3.png
:alt: output_20_3.png
:scale: 70%

output_20_3.png
:::

Output:

```
Running with:
Threshold: 20
Level: 3
```

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::MorphologicalWatershedImageFilter
```

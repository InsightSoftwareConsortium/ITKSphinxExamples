---
name: AssignContiguousLabelsToConnectedRegions
---

# Assign Contiguous Labels to Connected Regions in an Image

```{index} single: RelabelComponentImageFilter pair: connect; regions
```

## Synopsis

Assign contiguous labels to connected regions of an image.

## Results

:::{figure} AssignContiguousLabelsToConnectedRegions.png
:alt: VTK Window
:scale: 70%

Output In VTK Window
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::RelabelComponentImageFilter
```

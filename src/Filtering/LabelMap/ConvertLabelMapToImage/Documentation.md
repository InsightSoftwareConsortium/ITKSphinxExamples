---
name: ConvertLabelMapToImage
---

# Convert Label Map to Normal Image

```{index} single: LabelMapToLabelImageFilter pair: label; normal
```

## Synopsis

Convert a LabelMap to a normal image with different values representing each region

## Results

:::{figure} image.png
:alt: image.png
:scale: 70%

image.png
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::LabelMapToLabelImageFilter
```

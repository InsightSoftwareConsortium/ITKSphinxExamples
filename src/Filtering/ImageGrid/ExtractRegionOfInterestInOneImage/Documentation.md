---
name: ExtractRegionOfInterestInOneImage
---

# Extract Region of Interest in One Image

```{index} single: RegionOfInterestImageFilter
```

## Synopsis

Extract a given Region Of Interest (ROI) in a given image

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

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

```{eval-rst}
.. breathelink:: itk::RegionOfInterestImageFilter
```

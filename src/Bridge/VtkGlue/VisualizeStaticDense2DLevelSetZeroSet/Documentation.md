---
name: VisualizeStaticDense2DLevelSetZeroSet
---

# Visualize a Static Dense 2D Level-Set Zero-Set

```{index} single: VTKVisualizeImageLevelSetIsoValues single: BinaryImageToLevelSetImageAdaptor single: LevelSetDenseImage
```

## Synopsis

Visualize a static dense level-set function 2D's zero set. From the input
image, first an otsu thresholding technique is used to get a binary mask, which
is then converted to a dense level-set function.

## Results

:::{figure} cells.png
:alt: Input image (cells)
:scale: 100%

Input image
:::

:::{figure} levelsets.png
:alt: Static level-sets zero-sets
:scale: 100%

Static level-sets
:::

## Code

### C++

```{literalinclude} Code.cxx
:lines: 18-
```

## Classes demonstrated

% [breathelink:: itk::VTKVisualizeImageLevelSetIsoValues]
